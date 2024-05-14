// Copyright 2023 gRPC authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <grpc/support/port_platform.h>

#include "src/core/ext/filters/backend_metrics/backend_metric_filter.h"

#include <inttypes.h>
#include <stddef.h>

#include <functional>
#include <map>
#include <memory>
#include <utility>

#include "absl/strings/string_view.h"
#include "upb/base/string_view.h"
#include "upb/mem/arena.hpp"
#include "xds/data/orca/v3/orca_load_report.upb.h"

#include <grpc/impl/channel_arg_names.h>
#include <grpc/support/log.h>

#include "src/core/lib/channel/channel_stack.h"
#include "src/core/lib/channel/context.h"
#include "src/core/lib/channel/promise_based_filter.h"
#include "src/core/lib/config/core_configuration.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/experiments/experiments.h"
#include "src/core/lib/promise/context.h"
#include "src/core/lib/promise/map.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/lib/surface/channel_stack_type.h"
#include "src/core/lib/transport/metadata_batch.h"
#include "src/core/load_balancing/backend_metric_data.h"

namespace grpc_core {

const NoInterceptor BackendMetricFilter::Call::OnClientInitialMetadata;
const NoInterceptor BackendMetricFilter::Call::OnServerInitialMetadata;
const NoInterceptor BackendMetricFilter::Call::OnClientToServerMessage;
const NoInterceptor BackendMetricFilter::Call::OnServerToClientMessage;
const NoInterceptor BackendMetricFilter::Call::OnFinalize;

namespace {
absl::optional<std::string> MaybeSerializeBackendMetrics(
    BackendMetricProvider* provider) {
  if (provider == nullptr) return absl::nullopt;
  BackendMetricData data = provider->GetBackendMetricData();
  upb::Arena arena;
  xds_data_orca_v3_OrcaLoadReport* response =
      xds_data_orca_v3_OrcaLoadReport_new(arena.ptr());
  bool has_data = false;
  if (data.cpu_utilization != -1) {
    xds_data_orca_v3_OrcaLoadReport_set_cpu_utilization(response,
                                                        data.cpu_utilization);
    has_data = true;
  }
  if (data.mem_utilization != -1) {
    xds_data_orca_v3_OrcaLoadReport_set_mem_utilization(response,
                                                        data.mem_utilization);
    has_data = true;
  }
  if (data.application_utilization != -1) {
    xds_data_orca_v3_OrcaLoadReport_set_application_utilization(
        response, data.application_utilization);
    has_data = true;
  }
  if (data.qps != -1) {
    xds_data_orca_v3_OrcaLoadReport_set_rps_fractional(response, data.qps);
    has_data = true;
  }
  if (data.eps != -1) {
    xds_data_orca_v3_OrcaLoadReport_set_eps(response, data.eps);
    has_data = true;
  }
  for (const auto& p : data.request_cost) {
    xds_data_orca_v3_OrcaLoadReport_request_cost_set(
        response,
        upb_StringView_FromDataAndSize(p.first.data(), p.first.size()),
        p.second, arena.ptr());
    has_data = true;
  }
  for (const auto& p : data.utilization) {
    xds_data_orca_v3_OrcaLoadReport_utilization_set(
        response,
        upb_StringView_FromDataAndSize(p.first.data(), p.first.size()),
        p.second, arena.ptr());
    has_data = true;
  }
  for (const auto& p : data.named_metrics) {
    xds_data_orca_v3_OrcaLoadReport_named_metrics_set(
        response,
        upb_StringView_FromDataAndSize(p.first.data(), p.first.size()),
        p.second, arena.ptr());
    has_data = true;
  }
  if (!has_data) {
    return absl::nullopt;
  }
  size_t len;
  char* buf =
      xds_data_orca_v3_OrcaLoadReport_serialize(response, arena.ptr(), &len);
  return std::string(buf, len);
}
}  // namespace

const grpc_channel_filter BackendMetricFilter::kFilter =
    MakePromiseBasedFilter<BackendMetricFilter, FilterEndpoint::kServer>(
        "backend_metric");

absl::StatusOr<std::unique_ptr<BackendMetricFilter>>
BackendMetricFilter::Create(const ChannelArgs&, ChannelFilter::Args) {
  return std::make_unique<BackendMetricFilter>();
}

void BackendMetricFilter::Call::OnServerTrailingMetadata(ServerMetadata& md) {
  auto* ctx = &GetContext<
      grpc_call_context_element>()[GRPC_CONTEXT_BACKEND_METRIC_PROVIDER];
  if (ctx == nullptr) {
    if (GRPC_TRACE_FLAG_ENABLED(backend_metric_filter_trace)) {
      gpr_log(GPR_INFO, "[%p] No BackendMetricProvider.", this);
    }
    return;
  }
  absl::optional<std::string> serialized = MaybeSerializeBackendMetrics(
      reinterpret_cast<BackendMetricProvider*>(ctx->value));
  if (serialized.has_value() && !serialized->empty()) {
    if (GRPC_TRACE_FLAG_ENABLED(backend_metric_filter_trace)) {
      gpr_log(GPR_INFO, "[%p] Backend metrics serialized. size: %" PRIuPTR,
              this, serialized->size());
    }
    md.Set(EndpointLoadMetricsBinMetadata(),
           Slice::FromCopiedString(std::move(*serialized)));
  } else if (GRPC_TRACE_FLAG_ENABLED(backend_metric_filter_trace)) {
    gpr_log(GPR_INFO, "[%p] No backend metrics.", this);
  }
}

void RegisterBackendMetricFilter(CoreConfiguration::Builder* builder) {
  builder->channel_init()
      ->RegisterFilter<BackendMetricFilter>(GRPC_SERVER_CHANNEL)
      .IfHasChannelArg(GRPC_ARG_SERVER_CALL_METRIC_RECORDING);
}

}  // namespace grpc_core

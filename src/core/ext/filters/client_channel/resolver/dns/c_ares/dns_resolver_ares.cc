/*
 *
 * Copyright 2015 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <grpc/support/port_platform.h>

#if GRPC_ARES == 1

#include <limits.h>
#include <stdio.h>
#include <string.h>

#include "absl/container/inlined_vector.h"
#include "absl/strings/str_cat.h"

#include <grpc/support/alloc.h>
#include <grpc/support/string_util.h>

#include <address_sorting/address_sorting.h>

#include "src/core/ext/filters/client_channel/http_connect_handshaker.h"
#include "src/core/ext/filters/client_channel/lb_policy/grpclb/grpclb_balancer_addresses.h"
#include "src/core/ext/filters/client_channel/lb_policy_registry.h"
#include "src/core/ext/filters/client_channel/resolver/dns/c_ares/grpc_ares_wrapper.h"
#include "src/core/ext/filters/client_channel/resolver/dns/dns_resolver_selection.h"
#include "src/core/ext/filters/client_channel/resolver/dns/service_config_parser.h"
#include "src/core/ext/filters/client_channel/resolver_registry.h"
#include "src/core/ext/filters/client_channel/server_address.h"
#include "src/core/ext/filters/client_channel/service_config.h"
#include "src/core/lib/backoff/backoff.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/gpr/string.h"
#include "src/core/lib/gprpp/manual_constructor.h"
#include "src/core/lib/iomgr/iomgr_custom.h"
#include "src/core/lib/iomgr/resolve_address.h"
#include "src/core/lib/iomgr/timer.h"
#include "src/core/lib/iomgr/work_serializer.h"

namespace {
using ::grpc_event_engine::experimental::EventEngine;
}  // namespace

namespace grpc_core {

namespace {

class AresDnsResolver : public Resolver {
 public:
  explicit AresDnsResolver(ResolverArgs args);

  void StartLocked() override;

  void RequestReresolutionLocked() override;

  void ResetBackoffLocked() override;

  void ShutdownLocked() override;

 private:
  ~AresDnsResolver() override;

  void MaybeStartResolvingLocked();
  void StartResolvingLocked();

  static void OnNextResolution(void* arg, grpc_error_handle error);
  static void OnResolved(void* arg, grpc_error_handle error);
  void OnNextResolutionLocked(grpc_error_handle error);
  void OnResolvedLocked(grpc_error_handle error);

  /// DNS server to use (if not system default)
  std::string dns_server_;
  /// name to resolve (usually the same as target_name)
  std::string name_to_resolve_;
  /// channel args
  grpc_channel_args* channel_args_;
  std::shared_ptr<WorkSerializer> work_serializer_;
  std::unique_ptr<ResultHandler> result_handler_;
  /// pollset_set to drive the name resolution process
  grpc_pollset_set* interested_parties_;

  /// whether to request the service config
  bool request_service_config_;
  // whether or not to enable SRV DNS queries
  bool enable_srv_queries_;
  // timeout in milliseconds for active DNS queries
  int query_timeout_ms_;
  /// min interval between DNS requests
  grpc_millis min_time_between_resolutions_;

  /// closures used by the work_serializer
  grpc_closure on_next_resolution_;
  grpc_closure on_resolved_;
  /// are we currently resolving?
  bool resolving_ = false;
  /// the pending resolving request
  grpc_ares_request* pending_request_ = nullptr;
  /// next resolution timer
  bool have_next_resolution_timer_ = false;
  grpc_timer next_resolution_timer_;
  /// timestamp of last DNS request
  grpc_millis last_resolution_timestamp_ = -1;
  /// retry backoff state
  BackOff backoff_;
  /// currently resolving backend addresses
  std::unique_ptr<ServerAddressList> addresses_;
  /// currently resolving balancer addresses
  std::unique_ptr<ServerAddressList> balancer_addresses_;
  /// currently resolving service config
  char* service_config_json_ = nullptr;
  // has shutdown been initiated
  bool shutdown_initiated_ = false;
};

AresDnsResolver::AresDnsResolver(ResolverArgs args)
    : dns_server_(args.uri.authority()),
      name_to_resolve_(absl::StripPrefix(args.uri.path(), "/")),
      channel_args_(grpc_channel_args_copy(args.args)),
      work_serializer_(std::move(args.work_serializer)),
      result_handler_(std::move(args.result_handler)),
      interested_parties_(args.pollset_set),
      request_service_config_(!grpc_channel_args_find_bool(
          channel_args_, GRPC_ARG_SERVICE_CONFIG_DISABLE_RESOLUTION, true)),
      enable_srv_queries_(grpc_channel_args_find_bool(
          channel_args_, GRPC_ARG_DNS_ENABLE_SRV_QUERIES, false)),
      query_timeout_ms_(grpc_channel_args_find_integer(
          channel_args_, GRPC_ARG_DNS_ARES_QUERY_TIMEOUT_MS,
          {GRPC_DNS_ARES_DEFAULT_QUERY_TIMEOUT_MS, 0, INT_MAX})),
      min_time_between_resolutions_(grpc_channel_args_find_integer(
          channel_args_, GRPC_ARG_DNS_MIN_TIME_BETWEEN_RESOLUTIONS_MS,
          {1000 * 30, 0, INT_MAX})),
      backoff_(
          BackOff::Options()
              .set_initial_backoff(GRPC_DNS_INITIAL_CONNECT_BACKOFF_SECONDS *
                                   1000)
              .set_multiplier(GRPC_DNS_RECONNECT_BACKOFF_MULTIPLIER)
              .set_jitter(GRPC_DNS_RECONNECT_JITTER)
              .set_max_backoff(GRPC_DNS_RECONNECT_MAX_BACKOFF_SECONDS * 1000)) {
  // Closure initialization.
  GRPC_CLOSURE_INIT(&on_next_resolution_, OnNextResolution, this,
                    grpc_schedule_on_exec_ctx);
  GRPC_CLOSURE_INIT(&on_resolved_, OnResolved, this, grpc_schedule_on_exec_ctx);
}

AresDnsResolver::~AresDnsResolver() {
  GRPC_CARES_TRACE_LOG("resolver:%p destroying AresDnsResolver", this);
  grpc_channel_args_destroy(channel_args_);
}

void AresDnsResolver::StartLocked() {
  GRPC_CARES_TRACE_LOG("resolver:%p AresDnsResolver::StartLocked() is called.",
                       this);
  MaybeStartResolvingLocked();
}

void AresDnsResolver::RequestReresolutionLocked() {
  if (!resolving_) {
    MaybeStartResolvingLocked();
  }
}

void AresDnsResolver::ResetBackoffLocked() {
  if (have_next_resolution_timer_) {
    grpc_timer_cancel(&next_resolution_timer_);
  }
  backoff_.Reset();
}

void AresDnsResolver::ShutdownLocked() {
  shutdown_initiated_ = true;
  if (have_next_resolution_timer_) {
    grpc_timer_cancel(&next_resolution_timer_);
  }
  if (pending_request_ != nullptr) {
    grpc_cancel_ares_request_locked(pending_request_);
  }
}

void AresDnsResolver::OnNextResolution(void* arg, grpc_error_handle error) {
  AresDnsResolver* r = static_cast<AresDnsResolver*>(arg);
  GRPC_ERROR_REF(error);  // ref owned by lambda
  r->work_serializer_->Run([r, error]() { r->OnNextResolutionLocked(error); },
                           DEBUG_LOCATION);
}

void AresDnsResolver::OnNextResolutionLocked(grpc_error_handle error) {
  GRPC_CARES_TRACE_LOG(
      "resolver:%p re-resolution timer fired. error: %s. shutdown_initiated_: "
      "%d",
      this, grpc_error_std_string(error).c_str(), shutdown_initiated_);
  have_next_resolution_timer_ = false;
  if (error == GRPC_ERROR_NONE && !shutdown_initiated_) {
    if (!resolving_) {
      GRPC_CARES_TRACE_LOG(
          "resolver:%p start resolving due to re-resolution timer", this);
      StartResolvingLocked();
    }
  }
  Unref(DEBUG_LOCATION, "next_resolution_timer");
  GRPC_ERROR_UNREF(error);
}

void AresDnsResolver::OnResolved(void* arg, grpc_error_handle error) {
  AresDnsResolver* r = static_cast<AresDnsResolver*>(arg);
  GRPC_ERROR_REF(error);  // ref owned by lambda
  r->work_serializer_->Run([r, error]() { r->OnResolvedLocked(error); },
                           DEBUG_LOCATION);
}

void AresDnsResolver::OnResolvedLocked(grpc_error_handle error) {
  GPR_ASSERT(resolving_);
  resolving_ = false;
  gpr_free(pending_request_);
  pending_request_ = nullptr;
  if (shutdown_initiated_) {
    Unref(DEBUG_LOCATION, "OnResolvedLocked() shutdown");
    GRPC_ERROR_UNREF(error);
    return;
  }
  if (addresses_ != nullptr || balancer_addresses_ != nullptr) {
    Result result;
    if (addresses_ != nullptr) {
      result.addresses = std::move(*addresses_);
    }
    if (service_config_json_ != nullptr) {
      std::string service_config_string = ChooseServiceConfig(
          service_config_json_, &result.service_config_error);
      gpr_free(service_config_json_);
      if (result.service_config_error == GRPC_ERROR_NONE &&
          !service_config_string.empty()) {
        GRPC_CARES_TRACE_LOG("resolver:%p selected service config choice: %s",
                             this, service_config_string.c_str());
        result.service_config = ServiceConfig::Create(
            channel_args_, service_config_string, &result.service_config_error);
      }
    }
    absl::InlinedVector<grpc_arg, 1> new_args;
    if (balancer_addresses_ != nullptr) {
      new_args.push_back(
          CreateGrpclbBalancerAddressesArg(balancer_addresses_.get()));
    }
    result.args = grpc_channel_args_copy_and_add(channel_args_, new_args.data(),
                                                 new_args.size());
    result_handler_->ReturnResult(std::move(result));
    addresses_.reset();
    balancer_addresses_.reset();
    // Reset backoff state so that we start from the beginning when the
    // next request gets triggered.
    backoff_.Reset();
  } else {
    GRPC_CARES_TRACE_LOG("resolver:%p dns resolution failed: %s", this,
                         grpc_error_std_string(error).c_str());
    std::string error_message =
        absl::StrCat("DNS resolution failed for service: ", name_to_resolve_);
    result_handler_->ReturnError(grpc_error_set_int(
        GRPC_ERROR_CREATE_REFERENCING_FROM_COPIED_STRING(error_message.c_str(),
                                                         &error, 1),
        GRPC_ERROR_INT_GRPC_STATUS, GRPC_STATUS_UNAVAILABLE));
    // Set retry timer.
    // InvalidateNow to avoid getting stuck re-initializing this timer
    // in a loop while draining the currently-held WorkSerializer.
    // Also see https://github.com/grpc/grpc/issues/26079.
    ExecCtx::Get()->InvalidateNow();
    grpc_millis next_try = backoff_.NextAttemptTime();
    grpc_millis timeout = next_try - ExecCtx::Get()->Now();
    GRPC_CARES_TRACE_LOG("resolver:%p dns resolution failed (will retry): %s",
                         this, grpc_error_std_string(error).c_str());
    GPR_ASSERT(!have_next_resolution_timer_);
    have_next_resolution_timer_ = true;
    // TODO(roth): We currently deal with this ref manually.  Once the
    // new closure API is done, find a way to track this ref with the timer
    // callback as part of the type system.
    Ref(DEBUG_LOCATION, "retry-timer").release();
    if (timeout > 0) {
      GRPC_CARES_TRACE_LOG("resolver:%p retrying in %" PRId64 " milliseconds",
                           this, timeout);
    } else {
      GRPC_CARES_TRACE_LOG("resolver:%p retrying immediately", this);
    }
    grpc_timer_init(&next_resolution_timer_, next_try, &on_next_resolution_);
  }
  Unref(DEBUG_LOCATION, "dns-resolving");
  GRPC_ERROR_UNREF(error);
}

void AresDnsResolver::MaybeStartResolvingLocked() {
  // If there is an existing timer, the time it fires is the earliest time we
  // can start the next resolution.
  if (have_next_resolution_timer_) return;
  if (last_resolution_timestamp_ >= 0) {
    // InvalidateNow to avoid getting stuck re-initializing this timer
    // in a loop while draining the currently-held WorkSerializer.
    // Also see https://github.com/grpc/grpc/issues/26079.
    ExecCtx::Get()->InvalidateNow();
    const grpc_millis earliest_next_resolution =
        last_resolution_timestamp_ + min_time_between_resolutions_;
    const grpc_millis ms_until_next_resolution =
        earliest_next_resolution - grpc_core::ExecCtx::Get()->Now();
    if (ms_until_next_resolution > 0) {
      const grpc_millis last_resolution_ago =
          grpc_core::ExecCtx::Get()->Now() - last_resolution_timestamp_;
      GRPC_CARES_TRACE_LOG(
          "resolver:%p In cooldown from last resolution (from %" PRId64
          " ms ago). Will resolve again in %" PRId64 " ms",
          this, last_resolution_ago, ms_until_next_resolution);
      have_next_resolution_timer_ = true;
      // TODO(roth): We currently deal with this ref manually.  Once the
      // new closure API is done, find a way to track this ref with the timer
      // callback as part of the type system.
      Ref(DEBUG_LOCATION, "next_resolution_timer_cooldown").release();
      grpc_timer_init(&next_resolution_timer_,
                      ExecCtx::Get()->Now() + ms_until_next_resolution,
                      &on_next_resolution_);
      return;
    }
  }
  StartResolvingLocked();
}

void AresDnsResolver::StartResolvingLocked() {
  // TODO(roth): We currently deal with this ref manually.  Once the
  // new closure API is done, find a way to track this ref with the timer
  // callback as part of the type system.
  Ref(DEBUG_LOCATION, "dns-resolving").release();
  GPR_ASSERT(!resolving_);
  resolving_ = true;
  service_config_json_ = nullptr;
  pending_request_ = grpc_dns_lookup_ares_locked(
      dns_server_.c_str(), name_to_resolve_.c_str(), kDefaultSecurePort,
      interested_parties_, &on_resolved_, &addresses_,
      enable_srv_queries_ ? &balancer_addresses_ : nullptr,
      request_service_config_ ? &service_config_json_ : nullptr,
      query_timeout_ms_, work_serializer_);
  last_resolution_timestamp_ = grpc_core::ExecCtx::Get()->Now();
  GRPC_CARES_TRACE_LOG("resolver:%p Started resolving. pending_request_:%p",
                       this, pending_request_);
}

//
// Factory
//

class AresDnsResolverFactory : public ResolverFactory {
 public:
  bool IsValidUri(const URI& /*uri*/) const override { return true; }

  OrphanablePtr<Resolver> CreateResolver(ResolverArgs args) const override {
    return MakeOrphanable<AresDnsResolver>(std::move(args));
  }

  const char* scheme() const override { return "dns"; }
};

}  // namespace

}  // namespace grpc_core

static EventEngine::DNSResolver::LookupTaskHandle lookup_hostname(
    grpc_event_engine::experimental::EventEngine::DNSResolver::
        LookupHostnameCallback on_resolved,
    absl::string_view address, absl::string_view default_port,
    absl::Time deadline, grpc_pollset_set* /*interested_parties*/) {
  (void)on_resolved;
  (void)address;
  (void)default_port;
  (void)deadline;
  abort();
}

static EventEngine::DNSResolver::LookupTaskHandle lookup_srv_record(
    grpc_event_engine::experimental::EventEngine::DNSResolver::LookupSRVCallback
        on_resolved,
    absl::string_view name, absl::Time deadline,
    grpc_pollset_set* /*interested_parties*/) {
  (void)on_resolved;
  (void)name;
  (void)deadline;
  abort();
}

static EventEngine::DNSResolver::LookupTaskHandle lookup_txt_record(
    grpc_event_engine::experimental::EventEngine::DNSResolver::LookupTXTCallback
        on_resolved,
    absl::string_view name, absl::Time deadline,
    grpc_pollset_set* /*interested_parties*/) {
  (void)on_resolved;
  (void)name;
  (void)deadline;
  abort();
}

static void try_cancel_lookup(
    EventEngine::DNSResolver::LookupTaskHandle handle) {
  (void)handle;
  abort();
}

extern grpc_address_resolver_vtable* grpc_resolve_address_impl;
static grpc_address_resolver_vtable* default_resolver;

static grpc_error_handle blocking_resolve_address_ares(
    const char* name, const char* default_port,
    grpc_resolved_addresses** addresses) {
  return default_resolver->blocking_resolve_address(name, default_port,
                                                    addresses);
}

static grpc_address_resolver_vtable ares_resolver = {
    grpc_resolve_address_ares, blocking_resolve_address_ares,
    lookup_hostname,           lookup_srv_record,
    lookup_txt_record,         try_cancel_lookup};

static bool should_use_ares(const char* resolver_env) {
  // TODO(lidiz): Remove the "g_custom_iomgr_enabled" flag once c-ares support
  // custom IO managers (e.g. gevent).
  return !g_custom_iomgr_enabled &&
         (resolver_env == nullptr || strlen(resolver_env) == 0 ||
          gpr_stricmp(resolver_env, "ares") == 0);
}

static bool g_use_ares_dns_resolver;

void grpc_resolver_dns_ares_init() {
  grpc_core::UniquePtr<char> resolver =
      GPR_GLOBAL_CONFIG_GET(grpc_dns_resolver);
  if (should_use_ares(resolver.get())) {
    g_use_ares_dns_resolver = true;
    gpr_log(GPR_DEBUG, "Using ares dns resolver");
    address_sorting_init();
    grpc_error_handle error = grpc_ares_init();
    if (error != GRPC_ERROR_NONE) {
      GRPC_LOG_IF_ERROR("grpc_ares_init() failed", error);
      return;
    }
    if (default_resolver == nullptr) {
      default_resolver = grpc_resolve_address_impl;
    }
    grpc_set_resolver_impl(&ares_resolver);
    // grpc_core::ResolverRegistry::Builder::RegisterResolverFactory(
    //     absl::make_unique<grpc_core::AresDnsResolverFactory>());
  } else {
    g_use_ares_dns_resolver = false;
  }
}

void grpc_resolver_dns_ares_shutdown() {
  if (g_use_ares_dns_resolver) {
    address_sorting_shutdown();
    grpc_ares_cleanup();
  }
}

#else /* GRPC_ARES == 1 */

void grpc_resolver_dns_ares_init(void) {}

void grpc_resolver_dns_ares_shutdown(void) {}

#endif /* GRPC_ARES == 1 */

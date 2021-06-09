// Copyright 2021 The gRPC Authors
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

#include <grpc/event_engine/endpoint_config.h>

#include <grpc/impl/codegen/grpc_types.h>
#include <grpc/impl/codegen/log.h>

#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/event_engine/endpoint_config_internal.h"
#include "src/core/lib/gpr/useful.h"

namespace grpc_event_engine {
namespace experimental {

const EndpointConfig::Setting ChannelArgsEndpointConfig::Get(
    absl::string_view key) const {
  // TODO(hork): consider changing the API if string_view -> c_str is expensive.
  const grpc_arg* arg = grpc_channel_args_find(args_, std::string(key).c_str());
  if (arg == nullptr) {
    return absl::monostate();
  }
  switch (arg->type) {
    case GRPC_ARG_STRING:
      // TODO(hork): consider changing this to char* if the conversion is too
      // expensive. std::variant cannot hold references.
      return std::string(arg->value.string);
    case GRPC_ARG_INTEGER:
      return arg->value.integer;
    case GRPC_ARG_POINTER:
      return arg->value.pointer.p;
  }
  GPR_UNREACHABLE_CODE(return absl::monostate());
}

}  // namespace experimental
}  // namespace grpc_event_engine

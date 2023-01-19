// Copyright 2023 The gRPC Authors
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
#ifndef GRPC_CORE_EXT_FILTERS_CLIENT_CHANNEL_RESOLVER_DNS_EVENT_ENGINE_EVENT_ENGINE_CLIENT_CHANNEL_RESOLVER_H
#define GRPC_CORE_EXT_FILTERS_CLIENT_CHANNEL_RESOLVER_DNS_EVENT_ENGINE_EVENT_ENGINE_CLIENT_CHANNEL_RESOLVER_H
#include <grpc/support/port_platform.h>

#include "src/core/lib/resolver/resolver.h"
#include "src/core/lib/resolver/resolver_factory.h"

namespace grpc_event_engine {
namespace experimental {

class EventEngineClientChannelDNSResolverFactory
    : public grpc_core::ResolverFactory {
 public:
  absl::string_view scheme() const override { return "dns"; }
  bool IsValidUri(const grpc_core::URI& uri) const override;
  grpc_core::OrphanablePtr<grpc_core::Resolver> CreateResolver(
      grpc_core::ResolverArgs args) const override;
};

}  // namespace experimental
}  // namespace grpc_event_engine

#endif  // GRPC_CORE_EXT_FILTERS_CLIENT_CHANNEL_RESOLVER_DNS_EVENT_ENGINE_EVENT_ENGINE_CLIENT_CHANNEL_RESOLVER_H
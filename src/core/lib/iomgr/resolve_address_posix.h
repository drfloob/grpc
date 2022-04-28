//
// Copyright 2015 gRPC authors.
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
//

#ifndef GRPC_CORE_LIB_IOMGR_RESOLVE_ADDRESS_POSIX_H
#define GRPC_CORE_LIB_IOMGR_RESOLVE_ADDRESS_POSIX_H

#include <grpc/support/port_platform.h>

#include <functional>

#include <grpc/event_engine/event_engine.h>

#include "src/core/lib/iomgr/port.h"
#include "src/core/lib/iomgr/resolve_address.h"

namespace grpc_core {

// A DNS resolver which uses the native platform's getaddrinfo API.
class NativeDNSResolver : public DNSResolver {
 public:
  // Gets the singleton instance, creating it first if it doesn't exist
  static NativeDNSResolver* GetOrCreate();

  OrphanablePtr<DNSResolver::Request> ResolveName(
      absl::string_view name, absl::string_view default_port,
      grpc_pollset_set* interested_parties,
      grpc_event_engine::experimental::EventEngine::DNSResolver::
          LookupHostnameCallback on_done) override;

  absl::StatusOr<std::vector<
      grpc_event_engine::experimental::EventEngine::ResolvedAddress>>
  ResolveNameBlocking(absl::string_view name,
                      absl::string_view default_port) override;
};

}  // namespace grpc_core

#endif  // GRPC_CORE_LIB_IOMGR_RESOLVE_ADDRESS_POSIX_H

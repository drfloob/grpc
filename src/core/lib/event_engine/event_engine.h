/*
 *
 * Copyright 2020 gRPC authors.
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

#ifndef GRPC_CORE_LIB_EVENT_ENGINE_IOMGR_IOMGR_EVENT_ENGINE_H
#define GRPC_CORE_LIB_EVENT_ENGINE_IOMGR_IOMGR_EVENT_ENGINE_H

#ifdef GRPC_EVENT_ENGINE

#include <functional>
#include <vector>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/time/time.h"

#include "grpcpp/support/channel_arguments.h"

// DO NOT SUBMIT
//
// TODO:
// - explicitly define lifetimes and ownership of objects.
// - elaborate on constraints & pre-conditions for API usage.
// - supporting an escape hatch for those who want to work with FDs. Discussed
//   specifically treating our default & g3 EE impls specially using EE
//   identifiers.

namespace {
class SliceBuffer;
class ResourceManager;
}  // namespace

namespace grpc_core {

////////////////////////////////////////////////////////////////////////////////
// The EventEngine encapsulates all platform-specific behaviors related to low
// level network I/O, timers, asynchronous execution, and DNS resolution.
//
// A default cross-platform EventEngine instance is provided by gRPC, and can be
// overriden per channel or per server. Motivating uses cases for supporting
// custom EventEngines include the ability to hook into external event loops,
// and using different EventEngine instances for each channel to better insulate
// network I/O and callback processing from other channels.
//
// LIFESPAN AND OWNERSHIP
//
// gRPC takes shared ownership of EventEngines via std::shared_ptrs, and
// therefore EventEngines should remain valid as long as there are references to
// them.
//
// TODO: grpc_init() appears to be called multiple times (see
// grpc_channel_create).
////////////////////////////////////////////////////////////////////////////////
class EventEngine {
 public:
  // A basic callable function. The first argument to all callbacks is an
  // absl::Status indicating the status of the operation associated with this
  // callback.
  //
  // All callback types share these common Status meanings:
  // * OK: The callback is executed normally, no errors were encountered.
  // * CANCELLED: The callback was explicitly cancelled via the EventEngine API.
  using Callback = std::function<void(absl::Status)>;
  // A callback handle, used to cancel a callback.
  using TaskHandle = intptr_t;

  // An Endpoint represents one end of a connection between gRPC client
  // and server. Endpoints are created once connections are established, and
  // Endpoint operations are gRPC's means of communicating between clients and
  // servers.
  //
  // Endpoints must use the ResourceManager for all data buffer memory
  // allocations. gRPC allows applications to set memory constraints per Channel
  // using `ResourceQuota`s, and the implementation depends on all dynamic
  // memory allocation being handled by the quota system.
  class Endpoint {
   public:
    // Called when a new connection is established. This callback takes
    // ownership of the Endpoint and is responsible for ensuring the object is
    // destroyed.
    using OnConnectCallback = std::function<void(absl::Status, Endpoint)>;
    // Called in response to an Endpoint::Read request with the data that was
    // retrieved. If the status is not `OK`, the read was
    // unsuccessful and the content of the `data` buffer is undefined.
    using ReadCallback =
        std::function<void(absl::Status status, const SliceBuffer& data)>;
    virtual void Read(ReadCallback on_read, absl::Time deadline) = 0;
    // Write data out on the connection.
    virtual void Write(Callback on_write, const SliceBuffer& data, ,
                       absl::Time deadline) = 0;
    virtual void Close(Callback on_close) = 0;
    // These methods return an address in the format described in DNSResolver.
    virtual std::string GetPeerAddress() = 0;
    virtual std::string GetLocalAddress() = 0;
  };

  // An EventEngine Listener listens for incoming connection requests from gRPC
  // clients and initiates request processing once connections are
  // established.
  class Listener {
   public:
    // Called when the listener has accepted a new client connection. This
    // callback takes ownership of the Endpoint and is responsible for ensuring
    // the object is destroyed.
    //
    // TODO: does the accept callback need to mutate the Listener?
    using AcceptCallback =
        std::function<void(absl::Status, Endpoint, Listener&)>;
    // Bind an address/port to this Listener. Multiple ports can be bound to
    // this Listener before Listener::Start has been called.
    virtual absl::Status Bind(absl::string_view address,
                              absl::string_view port) = 0;
    virtual absl::Status Start() = 0;
    virtual absl::Status Shutdown() = 0;
  };

  // Factory method to create network listener.
  virtual absl::StatusOr<Listener> CreateListener(
      Listener::AcceptCallback on_accept, Callback on_shutdown,
      const ChannelArguments& args, SliceFactory& slice_factory) = 0;
  // Creates a network connection to a remote network listener.
  virtual absl::Status Connect(Endpoint::OnConnectCallback on_connect,
                               absl::string_view addr,
                               const ChannelArguments& args,
                               SliceFactory& slice_factory,
                               absl::Time deadline) = 0;

  class DNSResolver {
    // TODO: Be explicit about the meaning of Statuses.
    // A task handle for DNS Resolution requests.
    using LookupTaskHandle = intptr_t;
    // A callback method that's called with the collection of sockaddrs that
    // were resolved from a given target address.
    using LookupHostnameCallback =
        std::function<void(absl::Status, std::vector<Sockaddr>)>;
    using LookupSRVCallback =
        std::function<void(absl::Status, std::vector<SRVRecord>)>;
    using LookupTXTCallback = std::function<void(absl::Status, std::string)>;
    // Asynchronously resolve an address. `port` may be a non-numeric named
    // service port.
    virtual LookupTaskHandle LookupHostname(LookupHostnameCallback on_resolve,
                                            absl::string_view address,
                                            absl::string_view port,
                                            absl::Time deadline) = 0;
    virtual LookupTaskHandle LookupSRV(LookupSRVCallback on_resolve,
                                       absl::string_view name,
                                       absl::Time deadline) = 0;
    virtual LookupTaskHandle LookupTXT(LookupTXTCallback on_resolve,
                                       absl::string_view name,
                                       absl::Time deadline) = 0;
    // Cancel an asynchronous lookup operation.
    virtual void TryCancelLookup(LookupTaskHandle handle) = 0;
  };
  // Retrieves an instance of a DNSResolver.
  virtual absl::StatusOr<DNSResolver> GetDNSResolver() = 0;

  // Run a callback as soon as possible.
  virtual TaskHandle Run(Callback fn) = 0;
  // Synonymous with scheduling an alarm to run at time N.
  virtual TaskHandle RunAt(absl::Time when, Callback fn) = 0;
  // Immediately tries to cancel a callback.
  // Note that this is a "best effort" cancellation. No guarantee is made that
  // the callback will be cancelled, the call could be in any stage.
  //
  // There are three scenarios in which we may cancel a scheduled function:
  //   1. We cancel the execution before it has run.
  //   2. The callback has already run.
  //   3. We can't cancel it because it is "in flight".
  //
  // In all cases, the cancellation is still considered successful, the callback
  // will be run exactly once from either cancellation or from its activation.
  virtual void TryCancel(TaskHandle handle) = 0;
  // Immediately run all callbacks with status indicating the shutdown
  virtual absl::Status Shutdown() = 0;
};

absl::StatusOr<std::vector<Sockaddr>> BlockingLookupHostname(
    EventEngine& engine, absl::string_view address, absl::string_view port,
    absl::Time deadline);

// This is just here for discussion, it should be internal to gRPC. The purpose
// is to lazily instantiate a default EE instance if no global instance is
// provided, or return the explicitly-set global instance.
std::shared_ptr<EventEngine> grpc_get_default_event_engine();

}  // namespace grpc_core

#endif /* GRPC_EVENT_ENGINE */
#endif /* GRPC_CORE_LIB_EVENT_ENGINE_IOMGR_IOMGR_EVENT_ENGINE_H */

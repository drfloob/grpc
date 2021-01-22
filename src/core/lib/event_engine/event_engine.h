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
// - where do we need to support resource users? Can that be wrapped around this
//   API, or does it need to be embedded within it?
// - supporting an escape hatch for those who want to work with FDs. Discussed
//   specifically treating our default & g3 EE impls specially using EE
//   identifiers.

namespace grpc {

////////////////////////////////////////////////////////////////////////////////
// The EventEngine encapsulates all platform-specific behaviors related to low
// level network I/O, timers, asynchronous function and callback execution, and
// DNS resolution.
//
// A default cross-platform EventEngine instance is provided by gRPC, and can be
// overriden either globally or on a channel-by-channel basis. One may want to
// provide an EventEngine instance for each channel to better insulate network
// I/O from other channels, to control which threads run which callbacks, etc.
//
// LIFESPAN AND OWNERSHIP
//
// EventEngines are internally ref-counted, and therefore valid as long as
// there are references to them.
//
// TODO: grpc_init() appears to be called multiple times (see
// grpc_channel_create).
////////////////////////////////////////////////////////////////////////////////
class EventEngine {
 public:
  // Arbitrary data sent/received over the network.
  using DataBuffer = std::pair<void*, size_t>;
  // A basic callback. The first argument to all callbacks is an absl::Status
  // indicating the status of the operation associated with this callback.
  // For example, when cancelling a scheduled function before the timer has
  // expired, `CANCELLED` will be sent.
  using Callback = std::function<void(absl::Status)>;
  // A callback handle, used to cancel a callback.
  using TaskHandle = intptr_t;

  // An Endpoint represents one end of a connection between gRPC client
  // and server.
  //
  // Endpoints are created once connections are established, and Endpoint
  // operations are gRPC's means of communicating between clients and servers.
  class Endpoint {
   public:
    // Called when a new connection is established. This callback takes
    // ownership of the Endpoint and is responsible for ensuring the object is
    // destroyed.
    // DNS: expecting std::move(endpoint) into the callback argument.
    // TODO: Be explicit about the meaning of Statuses passed to the cb.
    using OnConnectCallback = std::function<void(absl::Status, Endpoint)>;
    // Called in response to an Endpoint::Read request with the data that was
    // retrieved. If the status is not `absl::StatusCode::kOk`, the read was
    // unsuccessful and the content of the `data` buffer is undefined.
    using ReadCallback =
        std::function<void(absl::Status status, const DataBuffer& data)>;
    virtual void Read(const ReadCallback& on_read, absl::Time deadline) = 0;
    // Write data out on the connection.
    virtual void Write(const DataBuffer& data, const Callback& on_write, ,
                       absl::Time deadline) = 0;
    // TODO: be explicit about on_close Status meanings.
    virtual void Close(const Callback& on_close) = 0;
    virtual absl::string_view GetPeerAddress() = 0;
    virtual absl::string_view GetLocalAddress() = 0;
  };
  // An EventEngine server listens for incoming connection requests from gRPC
  // clients and initiates request processing once connections are
  // established.
  class Server {
   public:
    // Called when the server has accepted a new client connection. This
    // callback takes ownership of the Endpoint and is responsible for ensuring
    // the object is destroyed.
    //
    // TODO: ask yang about the data buffer on accept.
    // TODO: does the accept callback need to mutate the Server?
    using AcceptCallback = std::function<void(absl::Status, Endpoint, Server&)>;
    virtual absl::Status Bind(absl::string_view address,
                              absl::string_view port) = 0;
    virtual absl::Status Start() = 0;
    virtual absl::Status Shutdown() = 0;
  };
  // Factory method to create network server.
  // TODO: be explicit about on_close Status meanings.
  virtual absl::StatusOr<Server> CreateServer(
      const ChannelArguments& args, const Server::AcceptCallback& on_accept,
      const Callback& on_shutdown) = 0;
  // Creates a network connection to a remote network server.
  virtual absl::Status CreateConnection(
      absl::string_view addr, const ChannelArguments& args,
      const Endpoint::OnConnectCallback& on_connect, absl::Time deadline) = 0;

  // TODO: define and vet the family of sockaddr types. Possibly expose
  // grpc_sockaddr_*.
  using GrpcSockaddr = sockaddr;
  struct GrpcSRVRecord {
    std::string host;
    int port = 0;
  };
  // A task handle for DNS Resolution requests.
  using LookupTaskHandle = intptr_t;
  // TODO: Be explicit about the meaning of Statuses.
  // A callback method that's called with the collection of sockaddrs that
  // were resolved from a given target address.
  using LookupHostnameCallback =
      std::function<void(absl::Status, std::vector<GrpcSockaddr>)>;
  using LookupSRVCallback =
      std::function<void(absl::Status, std::vector<GrpcSRVRecord>)>;
  using LookupTXTCallback = std::function<void(absl::Status, std::string)>;
  // Asynchronously resolve an address. `port` may be a non-numeric named
  // service port.
  virtual absl::StatusOr<LookupTaskHandle> LookupHostname(
      absl::string_view address, absl::string_view port,
      const ResolveCallback& on_resolve, absl::Time deadline) = 0;
  virtual absl::StatusOr<LookupTaskHandle> LookupSRV(
      absl::string_view name, const LookupSRVCallback& on_resolve,
      absl::Time deadline) = 0;
  virtual absl::StatusOr<LookupTaskHandle> LookupTXT(
      absl::string_view name, const LookupTXTCallback& on_resolve,
      absl::Time deadline) = 0;
  // TODO: might these Run* methods want to return errors?
  // Run a callback as soon as possible.
  virtual TaskHandle Run(const Callback& fn) = 0;
  // Synonymous with scheduling an alarm to run at time N.
  virtual TaskHandle RunAt(absl::Time when, const Callback& fn) = 0;
  // Immediately cancel a callback.
  //
  // There are three scenarios in which we may cancel a scheduled function:
  //   1. We normally cancel the execution
  //   2. The callback has already run
  //   3. We can't cancel it because it is "in flight".
  //
  //   In all of these cases, the cancellation is still considered
  //   successful. They are essentially distinguished in that the callback
  //   will be run exactly once from either the cancellation or from the
  //   activation.
  virtual absl::Status Cancel(const TaskHandle& handle);
  // Immediately run all callbacks with status indicating the shutdown
  virtual absl::Status Shutdown() = 0;
};

absl::StatusOr<std::string> BlockingResolve(EventEngine& engine,
                                            absl::string_view address,
                                            absl::string_view port,
                                            absl::Time deadline);

// Global registration of custom EventEngine. This instance will be used except
// when an EventEngine is provided at the Channel-level.
//
// gRPC does not assume ownership of this EventEngine. The application is
// responsible for ensuring that the EventEngine is valid until gRPC is shut
// down.
// TODO: confirm lifetime
// TODO: if a default EE is replaced, at what point can the previous EE be
// freed?
void grpc_set_default_event_engine(EventEngine* event_engine);

// This is just here for discussion, it should be internal to gRPC. The purpose
// is to lazily instantiate a default EE instance if no global instance is
// provided, or return the explicitly-set global instance.
EventEngine* grpc_get_default_event_engine();

}  // namespace grpc

#endif /* GRPC_EVENT_ENGINE */
#endif /* GRPC_CORE_LIB_EVENT_ENGINE_IOMGR_IOMGR_EVENT_ENGINE_H */

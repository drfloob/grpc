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

#ifndef GRPCPP_IO_H
#define GRPCPP_IO_H

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
//
// Example usage:
//    MyExecutor executor(/* ... */);
//    executor->Run(/* ... */);
//
//    MyIO io(/* ... */);  // possible dependency on executor
//    io->Connect(/* ... */);
//    absl::StatusOr<IO::Listener> listener = io->CreateListener(/* ... */);
//    if (!listener.ok()) { /* ... */ };
//    listener->Bind(/* ... */);
//    listener->Start();
//
//    MyResolver resolver(/* ... */);  // possible dependency on executor
//    resolver->Resolve(/* ... */);
//
//    // Set custom global IO implementations.
//    grpc_set_default_executor(executor);  // optional
//    grpc_set_default_io_engine(io);  // optional
//    grpc_set_default_resolver(resolver);  // optional
//
//    // Set custom IO implementations for a channel.
//    ChannelArguments args;
//    args.SetExecutor(executor);
//    args.SetIOEngine(io);
//    args.SetResolver(resolver);
//
// Deprecations:
// - Do we need to support binding to existing sockets?
// - Do we expose grpc_slice_buffer or reimplement in c++? Vote: reimplement.
//
//

namespace grpc {

// Forward declarations
class Executor;
class IOEngine;
class Resolver;

// This is a basic callback type. Any additional arguments the callback requires
// should be bound. INTERNAL: Akin to a grpc_closure, but simpler for public
// consumption.
using Callback = std::function<void(absl::Status)>;
// INTERNAL: akin to grpc_slice_buffer and grpc_byte_buffer. Those are fairly
// complex structures with multiple "internal only" fields, and those types
// aren't publicly exposed yet. For third-party implementations, a simple byte
// buffer is called for.
using ByteBuffer = std::pair<void*, size_t>;

// Global registration of custom defaults
void grpc_set_default_executor(Executor* executor);
void grpc_set_default_io_engine(IOEngine* io);
void grpc_set_default_resolver(Resolver* resolver);

// This is just here for discussion, it should be internal to gRPC. The purpose
// is to lazily instantiate a default instance if no global instance is
// provided, or return the explicitly-set global instance.
Executor* grpc_get_default_executor();
IO* grpc_get_default_io();
Resolver* grpc_get_default_resolver();

// TODO: do we need to support "cancel" features?
class Executor {
  // Run a callback as soon as possible.
  virtual absl::Status Run(const Callback& fn) = 0;
  // Synonymous with scheduling an alarm to run after N <time units>
  virtual absl::Status RunAfter(absl::Duration delay, const Callback& fn) = 0;
  // Synonymous with scheduling an alarm to run at time N.
  virtual absl::Status ScheduleAt(absl::Time when, const Callback& fn) = 0;
  // Synonymous with a repeated alarm
  virtual absl::Status RunRepeatedlyAfter(absl::Duration timeout,
                                          absl::Duration repeat,
                                          const Callback& fn);
  // Immediately run all callbacks with status indicating the shutdown.
  virtual absl::Status Shutdown() = 0;
};

class Resolver {
 public:
  using ResolveCallback =
      std::function<void(absl::Status status, std::vector<std::string> addrs)>;
  // Return the local hostname
  virtual std::string GetHostName() = 0;
  // Asynchronously resolve an address. `port` may be a non-numeric named
  // service port.
  virtual std::vector<std::string> Resolve(
      absl::string_view address, absl::string_view port,
      const ResolveCallback& on_resolve) = 0;
};

class IOEngine {
 public:
  // A network listener listenes for incoming connection requests from gRPC
  // clients and initiates request processing once connections are
  // established. This is named `IOEngine::Listener` to avoid confusion with a
  // gRPC Server, which relies on `IOEngine::Listeners` and generally operates
  // at a higher level.
  class Listener {
   public:
    virtual void Bind(absl::string_view address, absl::string_view port) = 0;
    virtual void Start() = 0;
    virtual void Shutdown() = 0;
  };
  // An endpoint caps a streaming channel between two communicating processes.
  // Examples may be: a tcp socket, <stdin+stdout>, or some shared memory.
  // Endpionts are created by Client and Server operations.
  class Endpoint {
   public:
    using ReadCallback =
        std::function<void(absl::Status status, const ByteBuffer& data)>;
    // construct, delete, copy, move
    virtual void Read(const ReadCallback& on_read) = 0;
    virtual void Write(const ByteBuffer& data, const Callback& on_write) = 0;
    virtual void Close(const Callback& on_close) = 0;
    virtual absl::string_view GetPeerAddress() = 0;
    virtual absl::string_view GetLocalAddress() = 0;
  };
  using OnConnectCallback =
      std::function<void(absl::Status, Endpoint& endpoint)>;
  using ListenerAcceptCallback =
      std::function<void(absl::Status status, Endpoint& endpoint,
                         Listener& listener, const ByteBuffer& data)>;
  // Factory method to create network listeners.
  virtual absl::StatusOr<Listener> CreateListener(
      const ChannelArguments& args, const ListenerAcceptCallback& on_accept,
      const Callback& on_shutdown) = 0;
  // Creates a network connection to a remote network listener.
  virtual absl::Status Connect(absl::string_view addr,
                               const ChannelArguments& args,
                               const OnConnectCallback& on_connect,
                               absl::Duration timeout) = 0;
};

}  // namespace grpc

#endif /* GRPCPP_IO_H */

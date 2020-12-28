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

#include "absl/time/time.h"

/*
 *
 * DO NOT SUBMIT
 *
 * Example usage:
 *    EventEngine engine = new MyCustomEventEngine(...);
 *    engine->dns->GetHostByName(...);
 *    Endpoint endpoint = engine->io->Connect(...);
 *    endpoint.Read(...);
 *    endpoint.Shutdown();
 *    auto handle = engine->task->Run(...);
 *    handle.Cancel();
 *
 *
 * Bonuses:
 * - This easily supports custom communication methods/transport layer
 * protocols.
 *
 *
 * TODO:
 * - assign types and args to interface methods
 * - better separate Endpoints vs the things that create Endpoints.
 *
 *
 * Endpoint questions:
 * - Do we need to support binding to existing sockets?
 *
 *
 * Open Questions:
 * - Will we need NotifyOn{Read,Write,Error} for Endpoints? (Hypothesis: no)
 * - Will we need NotifyWhen{Readable,Writable} for Endpoints? (Hypothesis: no)
 * - Do we want to support callback priority? (Hypothesis: probably)
 * - Do we need an exposed timer? (Hypothesis: no)
 *      We have an EM that allows closure execution after N <time units>
 *
 *
 */

namespace grpc {

class TaskRunner;
class DNSResolver;
class Endpoint;

// This groups together the customizable bits of gRPC's I/O functionality.
// EventEngine structs do not take ownership of any content; pointers must refer
// to valid objects that outlive the gRPC <DO NOT SUBMIT - define lifetime
// requirements>.
struct EventEngine {
  TaskRunner* task = nullptr;
  Endpoint* io = nullptr;
  DNSResolver* dns = nullptr;
};

// This is here just for discussion, it will be internal to gRPC. The purpose is
// to lazily instantiate a default instance if no instance is provided.
EventEngine get_default_event_engine();

class TaskRunner {
  // Run a callback as soon as possible.
  virtual TBDType<handle> Run(TBDType fn) = 0;
  // Synonymous with scheduling an alarm to run after N <time units>
  virtual TBDType<handle> RunAfter(absl::Duration delay, TBDType fn) = 0;
  // Synonymous with scheduling an alarm to run at time N.
  virtual TBDType<handle> ScheduleAt(absl::Time when, TBDType fn) = 0;
  // Synonymous with a repeated alarm
  virtual TBDType<handle> RunRepeatedAfter(absl::Duration timeout,
                                           absl::Duration repeat, TBDType cb);
  virtual absl::Status Cancel(TBDType<handle> handle) = 0;
};

class DNSResolver {
  virtual TBDType<handle> GetHostByName(absl::string_view name,
                                        absl::string_view dns_server,
                                        TBDType cb, absl::Duration timeout) = 0;
  virtual absl::Status Cancel(TBDType<handle> handle) = 0;
  // Do we need getsock?
};

class Server {
  virtual Server(const grpc_channel_args* args) = 0;
  virtual ~Server() = 0;
  virtual void Start() = 0;
  virtual void Bind(const grpc_resolved_address* addr) = 0;
  virtual void Shutdown() = 0;
}

class Client {
  virtual Client(const grpc_resolved_address* addr,
                 const grpc_channel_args* args) = 0;
}

class Endpoint {
  virtual void Read() = 0;
  virtual void Write() = 0;
  virtual void Close() = 0;
  virtual void GetPeerAddress() = 0;
  virtual void GetLocalAddress() = 0;
};

}  // namespace grpc

#endif /* GRPCPP_IO_H */

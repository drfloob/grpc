// Copyright 2022 The gRPC Authors
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
// See the License for the specific
#ifndef GRPC_CORE_LIB_EVENT_ENGINE_CLOSURE_UTIL_H
#define GRPC_CORE_LIB_EVENT_ENGINE_CLOSURE_UTIL_H
#include <grpc/support/port_platform.h>

#include <grpc/event_engine/event_engine.h>

#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/error.h"

namespace grpc_event_engine {
namespace experimental {

// EventEngine::Closure wrapper class for grpc_closure
// This creates a permanent Closure that the EventEngine does not own.
// The error will be unreffed at the end of Run(), or upon destruction
class WrappedGrpcClosure : public EventEngine::Closure {
 public:
  explicit WrappedGrpcClosure(grpc_closure* closure)
      : WrappedGrpcClosure(closure, nullptr) {}
  WrappedGrpcClosure(grpc_closure* closure, grpc_error_handle error)
      : closure_(closure), error_(error) {}
  ~WrappedGrpcClosure() override;

  // movable
  WrappedGrpcClosure(WrappedGrpcClosure&& other) noexcept;
  WrappedGrpcClosure& operator=(WrappedGrpcClosure&& other) noexcept;

  // call the callback using the given error_
  void Run() override;

  // error is passed to the underlying grpc_closure on Run()
  // if a previous error is already set, it will be unreffed
  void SetError(grpc_error_handle error);

 private:
  grpc_closure* closure_;
  grpc_error_handle error_;
};

// Creates an std::function that can be passed to EventEngine::Run
// error will be unreffed after the function is run.
std::function<void()> WrappedGrpcClosureFunction(grpc_closure* closure,
                                                 grpc_error_handle error);

}  // namespace experimental
}  // namespace grpc_event_engine

#endif  // GRPC_CORE_LIB_EVENT_ENGINE_CLOSURE_UTIL_H

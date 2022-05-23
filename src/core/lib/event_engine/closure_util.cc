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
#include <grpc/support/port_platform.h>

#include "src/core/lib/event_engine/closure_util.h"

#include <grpc/event_engine/event_engine.h>

#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/error.h"

extern grpc_core::DebugOnlyTraceFlag grpc_trace_closure;

namespace grpc_event_engine {
namespace experimental {

WrappedGrpcClosure::WrappedGrpcClosure(WrappedGrpcClosure&& other) noexcept
    : closure_(other.closure_), error_(other.error_) {
  if (this == &other) return;
  other.error_ = nullptr;
}

WrappedGrpcClosure& WrappedGrpcClosure::operator=(
    WrappedGrpcClosure&& other) noexcept {
  if (this == &other) return *this;
  closure_ = other.closure_;
  error_ = other.error_;
  other.error_ = nullptr;
  return *this;
}

WrappedGrpcClosure::~WrappedGrpcClosure() { GRPC_ERROR_UNREF(error_); }

void WrappedGrpcClosure::SetError(grpc_error_handle error) {
  if (error_ != nullptr) GRPC_ERROR_UNREF(error_);
  error_ = error;
}

namespace {
void RunClosure(grpc_closure* closure, grpc_error_handle error) {
  if (grpc_trace_closure.enabled()) {
    gpr_log(GPR_DEBUG,
            "(EventEngine): running closure %p: created [%s:%d]: run [%s:%d]",
            closure, closure->file_created, closure->line_created,
            closure->file_initiated, closure->line_initiated);
  }
  closure->cb(closure->cb_arg, error);
  if (grpc_trace_closure.enabled()) {
    gpr_log(GPR_DEBUG, "(EventEngine): closure %p finished", closure);
  }
  if (error != nullptr) GRPC_ERROR_UNREF(error);
}
}  // namespace

void WrappedGrpcClosure::Run() {
  RunClosure(closure_, error_);
  error_ = nullptr;
}

std::function<void()> WrappedGrpcClosureFunction(grpc_closure* closure,
                                                 grpc_error_handle error) {
  return [closure, error]() { RunClosure(closure, error); };
}

}  // namespace experimental
}  // namespace grpc_event_engine

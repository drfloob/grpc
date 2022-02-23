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
#ifndef GRPC_CORE_LIB_IOMGR_EVENT_ENGINE_PROMISE_H
#define GRPC_CORE_LIB_IOMGR_EVENT_ENGINE_PROMISE_H
#include <grpc/support/port_platform.h>

#include "src/core/lib/gprpp/sync.h"

namespace grpc_event_engine {
namespace experimental {

/// A minimal promise implementation.
///
/// This is light-duty, syntactical sugar around cv wait & signal, which is
/// useful in some cases. Can be replaced in the future using C++20's atomics
/// .wait() and .notify().
template <typename T>
class Promise {
 public:
  /// Blocks until Notify has been called, and will return the value passed to
  /// \a Notify.
  T& Wait() {
    absl::MutexLock lock(&mu_);
    if (!set_) {
      cv_.Wait(&mu_);
    }
    return val_;
  }
  /// Can only be called once. Will automatically unblock all waiting callers.
  void Notify(T&& val) {
    absl::MutexLock lock(&mu_);
    GPR_ASSERT(!set_);
    val_ = std::move(val);
    set_ = true;
    cv_.SignalAll();
  }

 private:
  absl::Mutex mu_;
  absl::CondVar cv_;
  T val_;
  bool set_ = false;
};

}  // namespace experimental
}  // namespace grpc_event_engine

#endif  // GRPC_CORE_LIB_IOMGR_EVENT_ENGINE_PROMISE_H

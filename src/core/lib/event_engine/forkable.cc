// Copyright 2022 gRPC authors.
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

#include "src/core/lib/event_engine/forkable.h"

grpc_core::TraceFlag grpc_trace_fork(false, "fork");

#ifdef GRPC_POSIX_FORK_ALLOW_PTHREAD_ATFORK

#include <pthread.h>

#include "absl/container/flat_hash_set.h"
#include "absl/types/optional.h"

#include "src/core/lib/debug/trace.h"
#include "src/core/lib/gprpp/fork.h"
#include "src/core/lib/gprpp/no_destruct.h"
#include "src/core/lib/gprpp/sync.h"
#include "src/core/lib/gprpp/time.h"

namespace grpc_event_engine {
namespace experimental {

namespace {
grpc_core::NoDestruct<grpc_core::Mutex> g_mu;
bool g_registered ABSL_GUARDED_BY(g_mu){false};
grpc_core::NoDestruct<absl::flat_hash_set<Forkable*>> g_forkables
    ABSL_GUARDED_BY(g_mu);
// DO NOT SUBMIT - testing. Ignoring a race here for now
absl::optional<grpc_core::Timestamp> gTestOnlyForkIsHappening;

}  // namespace

Forkable::Forkable() { ManageForkable(this); }

Forkable::~Forkable() { StopManagingForkable(this); }

void RegisterForkHandlers() {
  grpc_core::MutexLock lock(g_mu.get());
  if (!grpc_core::Fork::Enabled()) {
    GRPC_FORK_TRACE_LOG_STRING(
        "Forking is disabled, no fork handlers will be registered");
    return;
  }
  if (!std::exchange(g_registered, true)) {
    GRPC_FORK_TRACE_LOG_STRING("RegisterForkHandlers");
    pthread_atfork(PrepareFork, PostforkParent, PostforkChild);
  }
};

void PrepareFork() {
  gpr_log(GPR_DEBUG,
          "DO NOT SUBMIT: pid %d PrepareFork setting timestamp to %s on %p",
          getpid(), grpc_core::Timestamp::Now().ToString().c_str(),
          &gTestOnlyForkIsHappening);
  GRPC_FORK_TRACE_LOG_STRING("PrepareFork");
  grpc_core::MutexLock lock(g_mu.get());
  gTestOnlyForkIsHappening = grpc_core::Timestamp::Now();
  gpr_log(GPR_DEBUG, "DO NOT SUBMIT: gTestOnlyForkIsHappening.has_value() = %d",
          gTestOnlyForkIsHappening.has_value());
  for (auto* forkable : *g_forkables) {
    GRPC_FORK_TRACE_LOG("Calling PrepareFork for forkable::%p", forkable);
    forkable->PrepareFork();
  }
  GRPC_FORK_TRACE_LOG_STRING("PrepareFork finished");
}

void PostforkParent() {
  gpr_log(GPR_DEBUG,
          "DO NOT SUBMIT: PostforkParent resetting gTestOnlyForkIsHappening");
  grpc_core::MutexLock lock(g_mu.get());
  gTestOnlyForkIsHappening.reset();
  for (auto* forkable : *g_forkables) {
    GRPC_FORK_TRACE_LOG("Calling PostforkParent for forkable::%p", forkable);
    forkable->PostforkParent();
  }
  GRPC_FORK_TRACE_LOG_STRING("PostforkParent finished");
}

void PostforkChild() {
  gpr_log(GPR_DEBUG,
          "DO NOT SUBMIT: PostforkChild resetting gTestOnlyForkIsHappening");
  grpc_core::MutexLock lock(g_mu.get());
  gTestOnlyForkIsHappening.reset();
  for (auto* forkable : *g_forkables) {
    GRPC_FORK_TRACE_LOG("Calling PostforkChild for forkable::%p", forkable);
    forkable->PostforkChild();
  }
  GRPC_FORK_TRACE_LOG_STRING("PostforkChild finished");
}

absl::optional<grpc_core::Timestamp> ForkStartTimeIfForking() {
  auto ret = gTestOnlyForkIsHappening;
  gpr_log(GPR_DEBUG, "DO NOT SUBMIT: PID %d ForkStartTimeIfForking value? %d",
          getpid(), ret.has_value());
  return ret;
}

void ManageForkable(Forkable* forkable) {
  grpc_core::MutexLock lock(g_mu.get());
  g_forkables->insert(forkable);
}

void StopManagingForkable(Forkable* forkable) {
  grpc_core::MutexLock lock(g_mu.get());
  g_forkables->erase(forkable);
}

}  // namespace experimental
}  // namespace grpc_event_engine

#else  // GRPC_POSIX_FORK_ALLOW_PTHREAD_ATFORK

namespace grpc_event_engine {
namespace experimental {

Forkable::Forkable() {}
Forkable::~Forkable() {}

void RegisterForkHandlers() {}
void PrepareFork() {}
void PostforkParent() {}
void PostforkChild() {}

void ManageForkable(Forkable* /* forkable */) {}
void StopManagingForkable(Forkable* /* forkable */) {}

}  // namespace experimental
}  // namespace grpc_event_engine

#endif  // GRPC_POSIX_FORK_ALLOW_PTHREAD_ATFORK

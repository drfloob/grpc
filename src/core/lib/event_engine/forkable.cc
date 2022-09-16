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

#ifdef GRPC_POSIX_FORK_ALLOW_PTHREAD_ATFORK

#include <pthread.h>

#include "absl/container/flat_hash_set.h"

#include "src/core/lib/gprpp/no_destruct.h"
#include "src/core/lib/gprpp/sync.h"

namespace grpc_event_engine {
namespace experimental {

namespace {
grpc_core::NoDestruct<grpc_core::Mutex> g_mu;
bool g_registered ABSL_GUARDED_BY(g_mu){false};
grpc_core::NoDestruct<absl::flat_hash_set<Forkable*>> g_forkables
    ABSL_GUARDED_BY(g_mu);

// DO NOT SUBMIT
void PrintThreadCount() {
  gpr_log(GPR_DEBUG, "DO NOT SUBMIT: printing thread count 1");
  char command[50];
  int thread_count;
  int proc_id = getpid();
  sprintf(command, "ps H --no-headers %d | wc -l", proc_id);
  gpr_log(GPR_DEBUG, "DO NOT SUBMIT: printing thread count 2");
  FILE* thread_counter = popen(command, "r");
  gpr_log(GPR_DEBUG, "DO NOT SUBMIT: printing thread count 3");
  fscanf(thread_counter, "%d", &thread_count);
  gpr_log(GPR_DEBUG, "DO NOT SUBMIT: printing thread count 4");
  pclose(thread_counter);
  gpr_log(GPR_DEBUG, "DO NOT SUBMIT: proc_id=%d, thread_count=%d", proc_id,
          thread_count);
}
}  // namespace

Forkable::Forkable() { ManageForkable(this); }

Forkable::~Forkable() { StopManagingForkable(this); }

void RegisterForkHandlers() {
  grpc_core::MutexLock lock(g_mu.get());
  if (!std::exchange(g_registered, true)) {
    pthread_atfork(PrepareFork, PostforkParent, PostforkChild);
  }
};

void PrepareFork() {
  gpr_log(GPR_DEBUG, "DO NOT SUBMIT: Forkable::PrepareFork (check1)");
  PrintThreadCount();
  grpc_core::MutexLock lock(g_mu.get());
  for (auto* forkable : *g_forkables) {
    gpr_log(GPR_DEBUG, "DO NOT SUBMIT: PrepareForking forkable::%p", forkable);
    forkable->PrepareFork();
    gpr_log(GPR_DEBUG, "DO NOT SUBMIT: Done PrepareForking forkable::%p", forkable);
  }
  gpr_log(GPR_DEBUG, "DO NOT SUBMIT: Forkable::PrepareFork complete");
  PrintThreadCount();
}

void PostforkParent() {
  gpr_log(GPR_DEBUG, "DO NOT SUBMIT: Forkable::PostforkParent. pid=%d",
          static_cast<int>(getpid()));
  grpc_core::MutexLock lock(g_mu.get());
  for (auto* forkable : *g_forkables) {
    forkable->PostforkParent();
  }
}

void PostforkChild() {
  gpr_log(GPR_DEBUG, "DO NOT SUBMIT: Forkable::PostforkChild. pid=%d",
          static_cast<int>(getpid()));
  grpc_core::MutexLock lock(g_mu.get());
  for (auto* forkable : *g_forkables) {
    forkable->PostforkChild();
  }
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

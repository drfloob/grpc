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

#include <vector>

#ifdef GRPC_POSIX_FORK_ALLOW_PTHREAD_ATFORK

#include <pthread.h>

#include "absl/container/flat_hash_map.h"
#include "absl/strings/str_format.h"
#include "absl/strings/str_join.h"

#include "src/core/lib/gprpp/crash.h"
#include "src/core/lib/gprpp/no_destruct.h"
#include "src/core/lib/gprpp/sync.h"

namespace grpc_event_engine {
namespace experimental {

namespace {
grpc_core::NoDestruct<grpc_core::Mutex> g_mu;
bool g_registered ABSL_GUARDED_BY(g_mu){false};
grpc_core::NoDestruct<absl::flat_hash_set<Forkable*>> g_forkables
    ABSL_GUARDED_BY(g_mu);

void TopoSortInternal(
    absl::string_view name, std::vector<Forkable*> forkables,
    absl::flat_hash_set<std::string>& visited, std::vector<Forkable*>& sorted,
    absl::flat_hash_map<std::string, std::vector<Forkable*>>& named_forkables) {
  visited.emplace(name);
  if (!forkables.empty()) {
    for (absl::string_view dependency :
         forkables[0]->GetForkableDependencies()) {
      if (!visited.contains(dependency)) {
        TopoSortInternal(dependency, named_forkables[dependency], visited,
                         sorted, named_forkables);
      }
    }
  }
  sorted.insert(sorted.end(), forkables.begin(), forkables.end());
}

bool IsCyclic(
    absl::string_view forkable,
    absl::flat_hash_map<std::string, absl::flat_hash_set<std::string>>&
        forkable_dependency_map,
    absl::flat_hash_set<std::string>& visited,
    std::vector<std::string>& stack) {
  if (visited.contains(forkable)) {
    return false;
  }
  visited.insert(std::string(forkable));
  stack.emplace_back(forkable);
  for (absl::string_view dependency : forkable_dependency_map[forkable]) {
    if (!visited.contains(dependency) &&
        IsCyclic(dependency, forkable_dependency_map, visited, stack)) {
      return true;
    } else if (find(stack.begin(), stack.end(), dependency) != stack.end()) {
      return true;
    }
  }
  stack.pop_back();
  return false;
}

}  // namespace

// Sort forkables in topological order of dependency
// DO NOT SUBMIT(hork): move to anon ns again
std::vector<Forkable*> TopoSortForkables() ABSL_EXCLUSIVE_LOCKS_REQUIRED(g_mu) {
  // Map of name to object
  absl::flat_hash_map<std::string, std::vector<Forkable*>> named_forkables;
  for (auto* forkable : *g_forkables) {
    named_forkables[forkable->forkable_name()].emplace_back(forkable);
  }
  absl::flat_hash_set<std::string> visited;
  std::vector<Forkable*> sorted;
  for (const auto& named_forkable : named_forkables) {
    if (!visited.contains(named_forkable.first)) {
      TopoSortInternal(named_forkable.first, named_forkable.second, visited,
                       sorted, named_forkables);
    }
  }
  gpr_log(GPR_DEBUG, "DO NOT SUBMIT: topo sort");
  for (const auto& n : sorted) {
    gpr_log(GPR_DEBUG, "DO NOT SUBMIT:     %s::%p", n->forkable_name().c_str(),
            n);
  }
  grpc_core::Crash("DO NOT SUBMIT - testing");
  return sorted;
}

// Crash if there are cyclic dependencies in fork ordering
// TODO(hork): make this a static check, and optimize the algo for an
// incremental check under node additions.
// DO NOT SUBMIT(hork): move to anon ns
void AssertDAG() ABSL_EXCLUSIVE_LOCKS_REQUIRED(g_mu) {
  // build the class dependency map
  absl::flat_hash_map<std::string, absl::flat_hash_set<std::string>>
      forkable_dependency_map;
  for (auto* forkable : *g_forkables) {
    if (!forkable_dependency_map.contains(forkable->forkable_name())) {
      auto deps = forkable->GetForkableDependencies();
      forkable_dependency_map[forkable->forkable_name()].insert(deps.begin(),
                                                                deps.end());
    }
  }
  // // DO NOT SUBMIT(hork): trace logging
  // gpr_log(GPR_DEBUG, "DO NOT SUBMIT: node dump");
  // for (const auto& node : forkable_dependency_map) {
  //   gpr_log(GPR_DEBUG, "DO NOT SUBMIT: forkable::%s has deps (%s)",
  //           node.first.c_str(), absl::StrJoin(node.second, ",").c_str());
  // }

  // check for cycles
  absl::flat_hash_set<std::string> visited;
  std::vector<std::string> stack;
  for (const auto& node : forkable_dependency_map) {
    if (!visited.contains(node.first) &&
        IsCyclic(node.first, forkable_dependency_map, visited, stack)) {
      // DO NOT SUBMIT(hork): print the cycle
      grpc_core::Crash(absl::StrFormat(
          "Detected a cycle in the Forkable dependency graph. (%s->%s)",
          absl::StrJoin(stack, "->"), node.first));
    }
  }
}

Forkable::Forkable(grpc_core::SourceLocation location) {
  ManageForkable(this, location);
}

Forkable::~Forkable() { StopManagingForkable(this); }

void RegisterForkHandlers() {
  grpc_core::MutexLock lock(g_mu.get());
  if (!std::exchange(g_registered, true)) {
    pthread_atfork(PrepareFork, PostforkParent, PostforkChild);
  }
};

void PrepareFork() {
  grpc_core::MutexLock lock(g_mu.get());
  for (auto* forkable : TopoSortForkables()) {
    forkable->PrepareFork();
  }
}
void PostforkParent() {
  grpc_core::MutexLock lock(g_mu.get());
  for (auto* forkable : TopoSortForkables()) {
    forkable->PostforkParent();
  }
}

void PostforkChild() {
  grpc_core::MutexLock lock(g_mu.get());
  for (auto* forkable : TopoSortForkables()) {
    forkable->PostforkChild();
  }
}

void ManageForkable(Forkable* forkable, grpc_core::SourceLocation location) {
  gpr_log(GPR_DEBUG, "Managing Forkable::%p, created at [%s:%d]", forkable,
          location.file(), location.line());
  grpc_core::MutexLock lock(g_mu.get());
  g_forkables->insert(forkable);
  // AssertDAG();
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

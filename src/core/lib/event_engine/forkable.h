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
#ifndef GRPC_CORE_LIB_EVENT_ENGINE_FORKABLE_H
#define GRPC_CORE_LIB_EVENT_ENGINE_FORKABLE_H

#include <grpc/support/port_platform.h>

#include <string>

#include "absl/container/flat_hash_set.h"

#include "src/core/lib/gprpp/debug_location.h"

namespace grpc_event_engine {
namespace experimental {

// Register fork handlers with the system, enabling fork support.
//
// This provides pthread-based support for fork events. Any objects that
// implement Forkable can register themselves with this system using
// ManageForkable, and their respective methods will be called upon fork.
//
// This should be called once upon grpc_initialization.
void RegisterForkHandlers();

// Global callback for pthread_atfork's *prepare argument
void PrepareFork();
// Global callback for pthread_atfork's *parent argument
void PostforkParent();
// Global callback for pthread_atfork's *child argument
void PostforkChild();

// An interface to be implemented by EventEngines that wish to have managed fork
// support.
class Forkable {
 public:
  explicit Forkable(grpc_core::SourceLocation = {});
  virtual ~Forkable();
  virtual void PrepareFork() = 0;
  virtual void PostforkParent() = 0;
  virtual void PostforkChild() = 0;
  // Returns the name of the Forkable, for dependency resolution
  virtual std::string forkable_name() const = 0;
  // Returns the names of Forkables which must be handled before this object.
  // Any named Forkable will have its PrepareFork, PostforkParent, and
  // PostforkChild handlers called before the corresponding methods of this
  // object.
  // For example:
  //
  //    class Foo : public Forkable {
  //      absl::flat_hash_set<std::string> GetForkableDependencies() override
  //      {return "Bar"; } std::string forkable_name() { return "Foo"; }
  //    };
  //    class Bar : public Forkable {
  //      std::string forkable_name() { return "Bar"; }
  //    };
  //
  // This set of classes would result in the following ordering of fork handler
  // execution upon fork events:
  //
  //   Parent process: Bar::PrepareFork, Foo::PrepareFork
  //   -- fork --
  //   Parent process: Bar::PostforkParent, Foo::PostforkParent
  //   Child Process: Bar::PostforkChild, Foo::PostforkChild
  virtual absl::flat_hash_set<std::string> GetForkableDependencies() const {
    return {};
  }
};

// Add Forkables from the set of objects that are supported.
// Upon fork, each forkable will have its respective fork hooks called on
// the thread that invoked the fork.
//
// Relative ordering of fork callback operations is not guaranteed.
void ManageForkable(Forkable* forkable,
                    grpc_core::SourceLocation location = {});
// Remove a forkable from the managed set.
void StopManagingForkable(Forkable* forkable);

// DO NOT SUBMIT(hork): temporary
void AssertDAG();
// DO NOT SUBMIT(hork): temporary
std::vector<Forkable*> TopoSortForkables();

// DO NOT SUBMIT(hork): tmp
class N0 : public Forkable {
  void PrepareFork() override {}
  void PostforkParent() override {}
  void PostforkChild() override {}

  std::string forkable_name() const override { return "N0"; }
};

// DO NOT SUBMIT(hork): tmp
class N1 : public Forkable {
  void PrepareFork() override {}
  void PostforkParent() override {}
  void PostforkChild() override {}

  std::string forkable_name() const override { return "N1"; }
};

// DO NOT SUBMIT(hork): tmp
class N2 : public Forkable {
  void PrepareFork() override {}
  void PostforkParent() override {}
  void PostforkChild() override {}

  std::string forkable_name() const override { return "N2"; }
  absl::flat_hash_set<std::string> GetForkableDependencies() const override {
    return {"N3"};
  }
};

// DO NOT SUBMIT(hork): tmp
class N3 : public Forkable {
  void PrepareFork() override {}
  void PostforkParent() override {}
  void PostforkChild() override {}

  std::string forkable_name() const override { return "N3"; }
  absl::flat_hash_set<std::string> GetForkableDependencies() const override {
    return {"N1"};
  }
};


// DO NOT SUBMIT(hork): tmp
class N4 : public Forkable {
  void PrepareFork() override {}
  void PostforkParent() override {}
  void PostforkChild() override {}

  std::string forkable_name() const override { return "N4"; }
  absl::flat_hash_set<std::string> GetForkableDependencies() const override {
    return {"N0", "N1"};
  }
};

// DO NOT SUBMIT(hork): tmp
class N5 : public Forkable {
  void PrepareFork() override {}
  void PostforkParent() override {}
  void PostforkChild() override {}

  std::string forkable_name() const override { return "N5"; }
  absl::flat_hash_set<std::string> GetForkableDependencies() const override {
    return {"N0", "N2"};
  }
};


}  // namespace experimental
}  // namespace grpc_event_engine

#endif  // GRPC_CORE_LIB_EVENT_ENGINE_FORKABLE_H

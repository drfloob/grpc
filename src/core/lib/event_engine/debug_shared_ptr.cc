// Copyright 2023 The gRPC Authors
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
#include <memory>

#include <grpc/event_engine/event_engine.h>
#include <grpc/event_engine/internal/debug_shared_ptr.h>

namespace std {

atomic<int> shared_ptr<grpc_event_engine::experimental::EventEngine>::counter_{
    0};

unordered_map<int, string>
    shared_ptr<grpc_event_engine::experimental::EventEngine>::living_engines_;

unordered_map<grpc_event_engine::experimental::EventEngine*, atomic_int>
    shared_ptr<grpc_event_engine::experimental::EventEngine>::refcounts_;

}  // namespace std

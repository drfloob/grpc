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
#ifndef GRPC_CORE_LIB_IOMGR_EVENT_ENGINE_IOMGR_H
#define GRPC_CORE_LIB_IOMGR_EVENT_ENGINE_IOMGR_H
#include <grpc/event_engine/event_engine.h>

// This can be called anywhere in the EE-based iomgr impl where we need to
// access the global EE instance.
std::shared_ptr<grpc_event_engine::experimental::EventEngine>
grpc_iomgr_event_engine();

#endif  // GRPC_CORE_LIB_IOMGR_EVENT_ENGINE_IOMGR_H

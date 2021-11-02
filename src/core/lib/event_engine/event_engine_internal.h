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
#include <grpc/support/port_platform.h>

#include <grpc/event_engine/event_engine.h>

/// Access the shared global EventEngine instance.
///
/// The concept of a global EventEngine may go away in a post-iomgr world.
/// Strongly consider whether you could use \a CreateEventEngine instead.
grpc_event_engine::experimental::EventEngine* GetDefaultEventEngine();

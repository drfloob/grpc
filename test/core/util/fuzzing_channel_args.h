// Copyright 2023 gRPC authors.
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

#ifndef GRPC_TEST_CORE_UTIL_FUZZING_CHANNEL_ARGS_H
#define GRPC_TEST_CORE_UTIL_FUZZING_CHANNEL_ARGS_H

#include <grpc/support/port_platform.h>

#include "absl/strings/string_view.h"

#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/gprpp/ref_counted_ptr.h"
#include "src/core/lib/resource_quota/resource_quota.h"
#include "test/core/util/fuzzing_channel_args.pb.h"

namespace grpc_core {
namespace testing {

// Create ChannelArgs from a fuzzer configuration.
// resource_quota is an optional input/output argument. If it's not a nullptr,
// it will be set on the ChannelArgs object. If it is a nullptr, then it will be
// set to a ResourceQuota object iff the fuzzer configuration has requested that
// a ResourceQuota be created.
// The prefix_identifier is a name given to the ResourceQuota if one is created.
ChannelArgs CreateFuzzingChannelArgs(
    const grpc::testing::FuzzingChannelArgs& fuzzing_channel_args,
    absl::string_view prefix_identifier,
    RefCountedPtr<ResourceQuota>* resource_quota = nullptr);

}  // namespace testing
}  // namespace grpc_core

#endif  // GRPC_TEST_CORE_UTIL_FUZZING_CHANNEL_ARGS_H

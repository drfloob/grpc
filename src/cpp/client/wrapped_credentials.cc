// Copyright 2024 The gRPC Authors
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

#include "src/cpp/client/wrapped_credentials.h"

#include <memory>
#include <string>
#include <vector>

#include <grpc/grpc.h>
#include <grpc/grpc_security.h>
#include <grpcpp/security/credentials.h>
#include <grpcpp/support/channel_arguments.h>

namespace grpc {

WrappedChannelCredentials::WrappedChannelCredentials(
    grpc_channel_credentials* c_creds)
    : ChannelCredentials(c_creds) {
  GPR_ASSERT(c_creds != nullptr);
}

std::shared_ptr<Channel>
WrappedChannelCredentials::CreateChannelWithInterceptors(
    const std::string& target, const ChannelArguments& args,
    std::vector<
        std::unique_ptr<grpc::experimental::ClientInterceptorFactoryInterface>>
        interceptor_creators) {
  grpc_channel_args channel_args;
  args.SetChannelArgs(&channel_args);
  return grpc::CreateChannelInternal(
      args.GetSslTargetNameOverride(),
      grpc_channel_create(target.c_str(), c_creds(), &channel_args),
      std::move(interceptor_creators));
}

}  // namespace grpc

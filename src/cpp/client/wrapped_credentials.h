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
#ifndef GRPC_SRC_CPP_CLIENT_WRAPPED_CREDENTIALS_H
#define GRPC_SRC_CPP_CLIENT_WRAPPED_CREDENTIALS_H

#include <grpc/support/port_platform.h>

#include <memory>
#include <string>
#include <vector>

#include <grpc/grpc.h>
#include <grpc/grpc_security.h>
#include <grpcpp/security/credentials.h>

namespace grpc {

class WrappedChannelCredentials final : public ChannelCredentials {
 public:
  explicit WrappedChannelCredentials(grpc_channel_credentials* c_creds);
  ~WrappedChannelCredentials() override;

  std::shared_ptr<Channel> CreateChannelImpl(
      const std::string& target, const ChannelArguments& args) override;

  // Promoted to a public API for internal use
  grpc_channel_credentials* c_creds() const override { return c_creds_; }

 private:
  std::shared_ptr<Channel> CreateChannelWithInterceptors(
      const std::string& target, const ChannelArguments& args,
      std::vector<std::unique_ptr<
          grpc::experimental::ClientInterceptorFactoryInterface>>
          interceptor_creators) override;

  grpc_channel_credentials* const c_creds_ = nullptr;
};

class WrappedCallCredentials final : public CallCredentials {
 public:
  explicit WrappedCallCredentials(grpc_call_credentials* c_creds);
  ~WrappedCallCredentials() override;

  grpc_call_credentials* c_creds() override { return c_creds_; }
  bool ApplyToCall(grpc_call* call) override;
  std::string DebugString() override;

 private:
  grpc_call_credentials* const c_creds_;
};

// Creates a shared WrappedChannelCredentials if creds is non-null.
// Otherwise returns nullptr.
std::shared_ptr<WrappedChannelCredentials> WrapChannelCredentials(
    grpc_channel_credentials* creds);

// Creates a shared WrappedCallCredentials if creds is non-null.
// Otherwise returns nullptr.
std::shared_ptr<WrappedCallCredentials> WrapCallCredentials(
    grpc_call_credentials* creds);

}  // namespace grpc

#endif  // GRPC_SRC_CPP_CLIENT_WRAPPED_CREDENTIALS_H

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

#ifndef GRPC_CORE_LIB_IOMGR_EVENT_ENGINE_UV_IMPL_H
#define GRPC_CORE_LIB_IOMGR_EVENT_ENGINE_UV_IMPL_H

#include <grpc/support/port_platform.h>

#include <uv.h>

#include <grpc/event_engine/event_engine.h>

// TODO(nnoble): extract class declarations to header
class uvEngine;

// the base class to hold libuv socket information for both listeners and
// endpoints. it holds the uv_tcp_t object as well as the uvCloseCB counter,
// that allows it to self-delete once libuv is done with its object.
class uvTCPbase {
 public:
  uvTCPbase() = default;
  virtual ~uvTCPbase() = default;
  static void uvCloseCB(uv_handle_t* handle);
  int init(uvEngine* engine);
  uv_tcp_t tcp_;
  int to_close_ = 0;
};

class uvTCP final : public uvTCPbase {
 public:
  uvTCP(const grpc_event_engine::experimental::EndpointConfig& args,
        grpc_event_engine::experimental::SliceAllocator slice_allocator)
      : args_(args), slice_allocator_(std::move(slice_allocator)) {}
  virtual ~uvTCP() {
    GPR_ASSERT(write_bufs_ == nullptr);
    GPR_ASSERT(on_read_ == nullptr);
  };

  int init(uvEngine* engine);
  uv_timer_t write_timer_;
  uv_timer_t read_timer_;
  const grpc_event_engine::experimental::EndpointConfig args_;
  grpc_event_engine::experimental::SliceAllocator slice_allocator_;
  uv_write_t write_req_;
  uv_buf_t* write_bufs_ = nullptr;
  size_t write_bufs_count_ = 0;
  grpc_event_engine::experimental::SliceBuffer* read_sb_;
  grpc_event_engine::experimental::EventEngine::Callback on_writable_;
  grpc_event_engine::experimental::EventEngine::Callback on_read_;
  grpc_event_engine::experimental::EventEngine::ResolvedAddress peer_address_;
  grpc_event_engine::experimental::EventEngine::ResolvedAddress local_address_;
};

// the uv endpoint, a bit like the listener, is the wrapper around uvTCP,
// and doesn't have anything of its own beyond the uvTCP pointer, and
// the connect request data; the connect request data will be used
// before it's converted into a unique_ptr so it's fine to be stored
// there instead of the uvTCP class
class uvEndpoint final
    : public grpc_event_engine::experimental::EventEngine::Endpoint {
 public:
  uvEndpoint(const grpc_event_engine::experimental::EndpointConfig& args,
             grpc_event_engine::experimental::SliceAllocator slice_allocator);
  virtual ~uvEndpoint() override final;
  int init(uvEngine* engine);
  int populateAddressesUnsafe();
  virtual void Read(
      grpc_event_engine::experimental::EventEngine::Callback on_read,
      grpc_event_engine::experimental::SliceBuffer* buffer,
      absl::Time deadline) override final;
  virtual void Write(
      grpc_event_engine::experimental::EventEngine::Callback on_writable,
      grpc_event_engine::experimental::SliceBuffer* data,
      absl::Time deadline) override final;
  virtual const grpc_event_engine::experimental::EventEngine::ResolvedAddress*
  GetPeerAddress() const override final {
    return &uvTCP_->peer_address_;
  };
  virtual const grpc_event_engine::experimental::EventEngine::ResolvedAddress*
  GetLocalAddress() const override final {
    return &uvTCP_->local_address_;
  };
  absl::Status Connect(
      uvEngine* engine,
      grpc_event_engine::experimental::EventEngine::OnConnectCallback
          on_connect,
      const grpc_event_engine::experimental::EventEngine::ResolvedAddress&
          addr);
  uvEngine* getEngine() {
    return reinterpret_cast<uvEngine*>(uvTCP_->tcp_.loop->data);
  }
  // Internal use only.
  grpc_event_engine::experimental::SliceAllocator* GetSliceAllocator() const {
    return &uvTCP_->slice_allocator_;
  }
  uvTCP* uvTCP_ = nullptr;
  uv_connect_t connect_;
  grpc_event_engine::experimental::EventEngine::OnConnectCallback on_connect_ =
      nullptr;
  grpc_resource_user* ru_;
};

#endif  // GRPC_CORE_LIB_IOMGR_EVENT_ENGINE_UV_IMPL_H

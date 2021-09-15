/*
 *
 * Copyright 2015 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <grpc/support/port_platform.h>

#include "src/core/lib/iomgr/port.h"
#ifdef GRPC_POSIX_SOCKET_RESOLVE_ADDRESS

#include "src/core/lib/iomgr/sockaddr.h"

#include "src/core/lib/iomgr/resolve_address.h"

#include <string.h>
#include <sys/types.h>

#include <grpc/support/alloc.h>
#include <grpc/support/log.h>
#include <grpc/support/string_util.h>
#include <grpc/support/time.h>

#include "src/core/lib/gpr/string.h"
#include "src/core/lib/gpr/useful.h"
#include "src/core/lib/gprpp/host_port.h"
#include "src/core/lib/gprpp/thd.h"
#include "src/core/lib/iomgr/block_annotate.h"
#include "src/core/lib/iomgr/event_engine/resolved_address_internal.h"
#include "src/core/lib/iomgr/executor.h"
#include "src/core/lib/iomgr/iomgr_internal.h"
#include "src/core/lib/iomgr/unix_sockets_posix.h"
#include "src/core/lib/transport/error_utils.h"

namespace {
using ::grpc_event_engine::experimental::EventEngine;
}  // namespace

static grpc_error_handle posix_blocking_resolve_address(
    const char* name, const char* default_port,
    grpc_resolved_addresses** addresses) {
  grpc_core::ExecCtx exec_ctx;
  struct addrinfo hints;
  struct addrinfo *result = nullptr, *resp;
  int s;
  size_t i;
  grpc_error_handle err;

  std::string host;
  std::string port;
  /* parse name, splitting it into host and port parts */
  grpc_core::SplitHostPort(name, &host, &port);
  if (host.empty()) {
    err = grpc_error_set_str(
        GRPC_ERROR_CREATE_FROM_STATIC_STRING("unparseable host:port"),
        GRPC_ERROR_STR_TARGET_ADDRESS, grpc_slice_from_copied_string(name));
    goto done;
  }

  if (port.empty()) {
    if (default_port == nullptr) {
      err = grpc_error_set_str(
          GRPC_ERROR_CREATE_FROM_STATIC_STRING("no port in name"),
          GRPC_ERROR_STR_TARGET_ADDRESS, grpc_slice_from_copied_string(name));
      goto done;
    }
    port = default_port;
  }

  /* Call getaddrinfo */
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;     /* ipv4 or ipv6 */
  hints.ai_socktype = SOCK_STREAM; /* stream socket */
  hints.ai_flags = AI_PASSIVE;     /* for wildcard IP address */

  GRPC_SCHEDULING_START_BLOCKING_REGION;
  s = getaddrinfo(host.c_str(), port.c_str(), &hints, &result);
  GRPC_SCHEDULING_END_BLOCKING_REGION;

  if (s != 0) {
    /* Retry if well-known service name is recognized */
    const char* svc[][2] = {{"http", "80"}, {"https", "443"}};
    for (i = 0; i < GPR_ARRAY_SIZE(svc); i++) {
      if (port == svc[i][0]) {
        GRPC_SCHEDULING_START_BLOCKING_REGION;
        s = getaddrinfo(host.c_str(), svc[i][1], &hints, &result);
        GRPC_SCHEDULING_END_BLOCKING_REGION;
        break;
      }
    }
  }

  if (s != 0) {
    err = grpc_error_set_str(
        grpc_error_set_str(
            grpc_error_set_str(
                grpc_error_set_int(
                    GRPC_ERROR_CREATE_FROM_STATIC_STRING(gai_strerror(s)),
                    GRPC_ERROR_INT_ERRNO, s),
                GRPC_ERROR_STR_OS_ERROR,
                grpc_slice_from_static_string(gai_strerror(s))),
            GRPC_ERROR_STR_SYSCALL,
            grpc_slice_from_static_string("getaddrinfo")),
        GRPC_ERROR_STR_TARGET_ADDRESS, grpc_slice_from_copied_string(name));
    goto done;
  }

  /* Success path: set addrs non-NULL, fill it in */
  *addresses = static_cast<grpc_resolved_addresses*>(
      gpr_malloc(sizeof(grpc_resolved_addresses)));
  (*addresses)->naddrs = 0;
  for (resp = result; resp != nullptr; resp = resp->ai_next) {
    (*addresses)->naddrs++;
  }
  (*addresses)->addrs = static_cast<grpc_resolved_address*>(
      gpr_malloc(sizeof(grpc_resolved_address) * (*addresses)->naddrs));
  i = 0;
  for (resp = result; resp != nullptr; resp = resp->ai_next) {
    memcpy(&(*addresses)->addrs[i].addr, resp->ai_addr, resp->ai_addrlen);
    (*addresses)->addrs[i].len = resp->ai_addrlen;
    i++;
  }
  err = GRPC_ERROR_NONE;

done:
  if (result) {
    freeaddrinfo(result);
  }
  return err;
}

struct request {
  char* name;
  char* default_port;
  grpc_closure* on_done;
  grpc_resolved_addresses** addrs_out;
  grpc_closure request_closure;
  void* arg;
};
/* Callback to be passed to grpc Executor to asynch-ify
 * grpc_blocking_resolve_address */
static void do_request_thread(void* rp, grpc_error_handle /*error*/) {
  request* r = static_cast<request*>(rp);
  grpc_core::ExecCtx::Run(
      DEBUG_LOCATION, r->on_done,
      grpc_blocking_resolve_address(r->name, r->default_port, r->addrs_out));
  gpr_free(r->name);
  gpr_free(r->default_port);
  gpr_free(r);
}

static void posix_resolve_address(const char* name, const char* default_port,
                                  grpc_pollset_set* /*interested_parties*/,
                                  grpc_closure* on_done,
                                  grpc_resolved_addresses** addrs) {
  request* r = static_cast<request*>(gpr_malloc(sizeof(request)));
  GRPC_CLOSURE_INIT(&r->request_closure, do_request_thread, r, nullptr);
  r->name = gpr_strdup(name);
  r->default_port = gpr_strdup(default_port);
  r->on_done = on_done;
  r->addrs_out = addrs;
  grpc_core::Executor::Run(&r->request_closure, GRPC_ERROR_NONE,
                           grpc_core::ExecutorType::RESOLVER);
}

struct lookup_hostname_request {
  grpc_event_engine::experimental::EventEngine::DNSResolver::
      LookupHostnameCallback on_resolved_fn;
  grpc_closure on_resolved;
  std::string address;
  std::string default_port;
  grpc_closure request_closure;
  std::vector<EventEngine::ResolvedAddress> result;
};

static void do_request_thread_lookup_hostname(void* arg,
                                              grpc_error_handle error) {
  auto* lhr = static_cast<lookup_hostname_request*>(arg);
  if (error != GRPC_ERROR_NONE) {
    grpc_core::ExecCtx::Run(DEBUG_LOCATION, &lhr->on_resolved, error);
    return;
  }
  grpc_resolved_addresses* c_addrs_out;
  grpc_error_handle err = grpc_blocking_resolve_address(
      lhr->address.c_str(), lhr->default_port.c_str(), &c_addrs_out);
  if (err != GRPC_ERROR_NONE) {
    grpc_core::ExecCtx::Run(DEBUG_LOCATION, &lhr->on_resolved, err);
    return;
  }
  for (size_t i = 0; i < c_addrs_out->naddrs; i++) {
    lhr->result.push_back(
        grpc_event_engine::experimental::CreateResolvedAddress(
            c_addrs_out->addrs[i]));
  }
  grpc_core::ExecCtx::Run(DEBUG_LOCATION, &lhr->on_resolved, error);
}

static EventEngine::DNSResolver::LookupTaskHandle lookup_hostname(
    grpc_event_engine::experimental::EventEngine::DNSResolver::
        LookupHostnameCallback on_resolved,
    absl::string_view address, absl::string_view default_port,
    absl::Time /*deadline*/, grpc_pollset_set* /*interested_parties*/) {
  lookup_hostname_request* lhr = new lookup_hostname_request();
  GRPC_CLOSURE_INIT(&lhr->request_closure, do_request_thread_lookup_hostname,
                    lhr, nullptr);
  lhr->on_resolved_fn = std::move(on_resolved);
  GRPC_CLOSURE_INIT(
      &lhr->on_resolved,
      [](void* arg, grpc_error_handle error) {
        auto* lhr = static_cast<lookup_hostname_request*>(arg);
        if (error != GRPC_ERROR_NONE) {
          lhr->on_resolved_fn(grpc_error_to_absl_status(error));
          GRPC_ERROR_UNREF(error);
        } else {
          lhr->on_resolved_fn(lhr->result);
        }
        delete lhr;
      },
      lhr, nullptr);
  lhr->address = std::string(address);
  lhr->default_port = std::string(default_port);
  grpc_core::Executor::Run(&lhr->request_closure, GRPC_ERROR_NONE,
                           grpc_core::ExecutorType::RESOLVER);
  return {-1, -1};
}

static EventEngine::DNSResolver::LookupTaskHandle lookup_srv_record(
    grpc_event_engine::experimental::EventEngine::DNSResolver::LookupSRVCallback
        on_resolved,
    absl::string_view /*name*/, absl::Time /*deadline*/,
    grpc_pollset_set* /*interested_parties*/) {
  // DO NOT SUBMIT(hork): run asynchronously?
  on_resolved(
      absl::UnimplementedError("Posix iomgr does not support SRV queries"));
  return {-1, -1};
}

static EventEngine::DNSResolver::LookupTaskHandle lookup_txt_record(
    grpc_event_engine::experimental::EventEngine::DNSResolver::LookupTXTCallback
        on_resolved,
    absl::string_view /*name*/, absl::Time /*deadline*/,
    grpc_pollset_set* /*interested_parties*/) {
  // DO NOT SUBMIT(hork): run asynchronously?
  on_resolved(
      absl::UnimplementedError("Posix iomgr does not support TXT queries"));
  return {-1, -1};
}

static void try_cancel_lookup(
    EventEngine::DNSResolver::LookupTaskHandle /*handle*/) {
  // Posix iomgr does not support DNS cancellation
}

grpc_address_resolver_vtable grpc_posix_resolver_vtable = {
    posix_resolve_address, posix_blocking_resolve_address,
    lookup_hostname,       lookup_srv_record,
    lookup_txt_record,     try_cancel_lookup};
#endif

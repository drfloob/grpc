/*
 *
 * Copyright 2020 gRPC authors.
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

#ifdef GRPC_EVENT_ENGINE

// DO NOT SUBMIT - implement

grpc_socket_vtable grpc_event_engine_socket_vtable = {
    socket_init,        socket_connect, socket_destroy, socket_shutdown,
    socket_close,       socket_write,   socket_read,    socket_getpeername,
    socket_getsockname, socket_bind,    socket_listen,  socket_accept};

#endif /* GRPC_EVENT_ENGINE */

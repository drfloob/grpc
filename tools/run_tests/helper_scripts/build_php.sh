#!/bin/bash
# Copyright 2015 gRPC authors.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

set -ex

CONFIG=dbg

# change to grpc repo root
cd "$(dirname "$0")/../../.."

export CFLAGS="-Wno-parentheses-equality -O0 -gmlt"
export CXXFLAGS="-O0 -gmlt"

# build C core first
make -j"${GRPC_RUN_TESTS_JOBS}" EMBED_OPENSSL=true EMBED_ZLIB=true static_c shared_c

repo_root="$(pwd)"
export GRPC_LIB_SUBDIR=libs/$CONFIG
export CFLAGS="-Wno-parentheses-equality -O0 -gmlt"
export CXXFLAGS="-O0 -gmlt"

# build php
cd src/php/ext/grpc
phpize
./configure --enable-grpc="${repo_root}" --enable-coverage --enable-tests
make -j"${GRPC_RUN_TESTS_JOBS}"

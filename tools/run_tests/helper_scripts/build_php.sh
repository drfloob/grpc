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

set -x

CONFIG=dbg

# change to grpc repo root
cd "$(dirname "$0")/../../.."

export CFLAGS="-Wno-parentheses-equality -O0 -gmlt"
export CXXFLAGS="-O0 -gmlt"

# build C core first
make -j16 EMBED_OPENSSL=true EMBED_ZLIB=true static_c shared_c
find . -name 'grpc.so' -exec sh -c "nm -aU {} | grep EventEngine " \; || true
find . -name 'libgrpc.*' -exec sh -c "nm -aU {} | grep EventEngine " \; || true
repo_root="$(pwd)"
export GRPC_LIB_SUBDIR=libs/$CONFIG
# export CFLAGS="-Wno-parentheses-equality -O0 -gmlt"
# export CXXFLAGS="-O0 -gmlt"

# build php
cd src/php/ext/grpc
phpize
./configure --enable-grpc="${repo_root}" --enable-tests
echo "DO NOT SUBMIT - makefile -----------------------------------"
ls -l
cat Makefile
echo "DO NOT SUBMIT - makefile -----------------------------------"
export CFLAGS="-Wno-parentheses-equality -O0 -gmlt"
export CXXFLAGS="-O0 -gmlt"
make -j16
file grpc.la || true
nm -aU grpc.la | grep EventEngine || true
file ./.libs/grpc.lai || true
nm -aU ./.libs/grpc.lai | grep EventEngine || true
nm -aU ./.libs/grpc.so | grep EventEngine || true
find . -name 'grpc.so' -exec sh -c "nm -aU {} | grep EventEngine " \; || true
find . -name 'libgrpc.*' -exec sh -c "nm -aU {} | grep EventEngine " \; || true

# this is where the file is installed
nm -aU /Volumes/BuildData/tmpfs/altsrc/github/grpc/workspace_php7_macos_dbg_native/src/php/ext/grpc/modules/grpc.so | grep EventEngine || true

exit 42

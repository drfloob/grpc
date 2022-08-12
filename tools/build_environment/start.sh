#!/usr/bin/env bash

# Copyright 2022 The gRPC Authors
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http:#www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# This script will start a dockerized build environment, pre-populated with all
# of the tools you need to build and sanitize your codebase.

# Inspired by the apache beam development environment
# https://github.com/apache/beam/blob/774745b1a3e89f284d627fdd0d56290116a19de7/start-build-env.sh

set -e

err() {
    echo "[$(date +'%Y-%m-%dT%H:%M:%S%z')]: $*" >&2
}

BUILD_ENV_DIR="$(dirname $0)"

# change to root directory
cd $(dirname $0)/../..
REPO_ROOT=$(pwd)
CONTAINER_NAME=grpc-dev-${USER}-$$

if [ ! -x "$(command -v docker)" ]; then
    err "Please install docker to use this build environment."
    exit 1
fi

SANITY_DOCKERFILE_DIR=tools/dockerfile/test/sanity

# Build the base sanitizer image
docker build -t grpc-build -f ${SANITY_DOCKERFILE_DIR}/Dockerfile ${SANITY_DOCKERFILE_DIR}

USER_NAME=${SUDO_USER:=$USER}
USER_ID=$(id -u "${USER_NAME}")

if [ "$(uname -s)" = "Linux" ]; then
    DOCKER_GROUP_ID=$(getent group docker | cut -d':' -f3)
    GROUP_ID=$(id -g "${USER_NAME}")
    # man docker-run
    # When using SELinux, mounted directories may not be accessible
    # to the container. To work around this, with Docker prior to 1.7
    # one needs to run the "chcon -Rt svirt_sandbox_file_t" command on
    # the directories. With Docker 1.7 and later the z mount option
    # does this automatically.
    if command -v selinuxenabled >/dev/null && selinuxenabled; then
        DCKR_VER=$(docker -v |
            awk '$1 == "Docker" && $2 == "version" {split($3,ver,".");print ver[1]"."ver[2]}')
        DCKR_MAJ=${DCKR_VER%.*}
        DCKR_MIN=${DCKR_VER#*.}
        if [ "${DCKR_MAJ}" -eq 1 ] && [ "${DCKR_MIN}" -ge 7 ] ||
            [ "${DCKR_MAJ}" -gt 1 ]; then
            V_OPTS=:z
        else
            for d in "${PWD}" "${HOME}/.m2"; do
                ctx=$(stat --printf='%C' "$d" | cut -d':' -f3)
                if [ "$ctx" != svirt_sandbox_file_t ] && [ "$ctx" != container_file_t ]; then
                    printf 'INFO: SELinux is enabled.\n'
                    printf '\tMounted %s may not be accessible to the container.\n' "$d"
                    printf 'INFO: If so, on the host, run the following command:\n'
                    printf '\t# chcon -Rt svirt_sandbox_file_t %s\n' "$d"
                fi
            done
        fi
    fi
else
    err "Host platform not yet supported: $(uname -s)"
    exit 2
fi

# Set the home directory in the Docker container.
DOCKER_HOME_DIR=${DOCKER_HOME_DIR:-/home/${USER_NAME}}

docker build -t "grpc-build-${USER_ID}" \
  --build-arg GROUP_ID=$GROUP_ID \
  --build-arg USER_ID=$USER_ID \
  --build-arg USER_NAME=$USER_NAME \
  --build-arg DOCKER_HOME_DIR=$DOCKER_HOME_DIR \
  -f ${BUILD_ENV_DIR}/Dockerfile ${BUILD_ENV_DIR}

echo ""
echo "Docker image build completed."
echo "=============================================================================================="
echo ""

DOCKER_SOCKET_MOUNT=""
if [ -S /var/run/docker.sock ];
then
  DOCKER_SOCKET_MOUNT="-v /var/run/docker.sock:/var/run/docker.sock${V_OPTS:-}"
fi

COMMAND=( "$@" )
if [ $# -eq 0 ];
then
  COMMAND=( "bash" )
fi

docker run --rm=true -i -t \
    --name "${CONTAINER_NAME}" \
    --network=host \
    -v "${PWD}:${DOCKER_HOME_DIR}/grpc${V_OPTS:-}" \
    -w "${DOCKER_HOME_DIR}/grpc" \
    ${DOCKER_SOCKET_MOUNT} \
    -u "${USER_ID}" \
    "grpc-build-${USER_ID}" "${COMMAND[@]}"

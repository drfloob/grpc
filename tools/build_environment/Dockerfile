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

FROM grpc-build

ARG GROUP_ID
ARG USER_ID
ARG USER_NAME
ARG DOCKER_HOME_DIR

RUN rm -f /var/log/faillog /var/log/lastlog
RUN groupadd --non-unique -g ${GROUP_ID} ${USER_NAME}
RUN apt-get install -y sudo docker.io
# RUN groupmod -g ${DOCKER_GROUP_ID} docker
RUN useradd -g ${GROUP_ID} -u ${USER_ID} -k /root -m ${USER_NAME} -d "${DOCKER_HOME_DIR}"
RUN echo "${USER_NAME} ALL=NOPASSWD: ALL" > "/etc/sudoers.d/grpc-build-${USER_ID}"
ENV HOME "${DOCKER_HOME_DIR}"
COPY motd /etc/motd
RUN echo "cat /etc/motd" >> "${DOCKER_HOME_DIR}/.bashrc"

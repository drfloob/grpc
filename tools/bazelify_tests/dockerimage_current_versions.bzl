# Copyright 2023 The gRPC Authors
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

"""
This file is generated by generate_dockerimage_current_versions_bzl.sh
It makes the info from testing docker image *.current_version files
accessible to bazel builds.
"""

DOCKERIMAGE_CURRENT_VERSIONS = {
    "third_party/rake-compiler-dock/rake_aarch64-linux.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/rake_aarch64-linux@sha256:3a357ffa21f97b7f9e4c6e404f95fbb2400b0c3dd7340e1e663951eb4000ff89",
    "third_party/rake-compiler-dock/rake_arm64-darwin.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/rake_arm64-darwin@sha256:28a88cb72472608f716aa60e7f1f22182c60809cc4e96c035c0e38e708e4e9be",
    "third_party/rake-compiler-dock/rake_x64-mingw-ucrt.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/rake_x64-mingw-ucrt@sha256:d6d34c393a66a3b36bb62364b149bd6e84f342258b586bfd0301972d9bdda34c",
    "third_party/rake-compiler-dock/rake_x64-mingw32.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/rake_x64-mingw32@sha256:473aebab86ea23245452dfaf7d50ca00caca3c4ed4b6931af0338723b65e1f1e",
    "third_party/rake-compiler-dock/rake_x86-linux.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/rake_x86-linux@sha256:7d61256637aaf933c1af299f80521e166484bdf081c60f8955ef9a61c338ba4d",
    "third_party/rake-compiler-dock/rake_x86-mingw32.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/rake_x86-mingw32@sha256:2be5e0decccc23f8b7ac1b2d5edd21ea814868dcfe08b955749167fd22f99a20",
    "third_party/rake-compiler-dock/rake_x86_64-darwin.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/rake_x86_64-darwin@sha256:e01c02a18130b9669da57bb28b3f6c30458511e20eae5821b3899a41e09f394a",
    "third_party/rake-compiler-dock/rake_x86_64-linux.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/rake_x86_64-linux@sha256:e917daf2c6f60e47e1b881ebb93fe851e53284c6abc2d910e1b9bc16d8e39cdf",
    "tools/dockerfile/distribtest/cpp_debian11_aarch64_cross_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/cpp_debian11_aarch64_cross_x64@sha256:5de93f45dee2263d45f8934a17bf820847145f69c49338fb491a9690cf346994",
    "tools/dockerfile/distribtest/cpp_debian11_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/cpp_debian11_x64@sha256:5cf417d8fc575685922959292b3eae91844c2480040b0c605485eae009eb67db",
    "tools/dockerfile/distribtest/csharp_alpine_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/csharp_alpine_x64@sha256:17d9f984e34b978114e5835224f7ad9c9ac59b2a101787efb0f4d265efd592e0",
    "tools/dockerfile/distribtest/csharp_centos7_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/csharp_centos7_x64@sha256:ec715dd5fbd621789e7598c8d4ac346a7b4037b0cc83fbb29990dc8e4c1f1a13",
    "tools/dockerfile/distribtest/csharp_debian11_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/csharp_debian11_x64@sha256:e79a68c91a6ba8a2cb512671c96565f67b9e6efefb05c75eefd3b57c51f4d705",
    "tools/dockerfile/distribtest/csharp_dotnet31_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/csharp_dotnet31_x64@sha256:1fb798ba335d0f010ea988723e375f5b8766a8107a814c39c7b3d89558c15e98",
    "tools/dockerfile/distribtest/csharp_dotnet5_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/csharp_dotnet5_x64@sha256:9234c28596f48f82628ca58437a20c63148cd818a10bd15f7b85490bb432d923",
    "tools/dockerfile/distribtest/csharp_ubuntu2204_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/csharp_ubuntu2204_x64@sha256:2ce824e9dcd7b3eb6a6bf004298d33c9720fd362939b08cb7cdd6808d7ecf807",
    "tools/dockerfile/distribtest/php8_debian12_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/php8_debian12_x64@sha256:f81b0702bd28823f12402cfabc8eaecebd0fd2b58a28ba93ef40f9832b25196f",
    "tools/dockerfile/distribtest/python_alpine_aarch64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/python_alpine_aarch64@sha256:4178c853e872927b37627e0201e72adfcae47edcb5f80d441bbfaf55db4f92e9",
    "tools/dockerfile/distribtest/python_alpine_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/python_alpine_x64@sha256:7b5ec7e008baa5d3f83daeca7fee53fee8f5f03d77df8c58104626eb4c2a239b",
    "tools/dockerfile/distribtest/python_arch_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/python_arch_x64@sha256:cc4c9bafe3bfee407bb1bec22d8c62c1a29db718a3926b9073128d311067f7bb",
    "tools/dockerfile/distribtest/python_bullseye_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/python_bullseye_x64@sha256:9d4281e3c006dc9092417aef8916e5e5a2e4893df21ab7482fb6902025b96eb8",
    "tools/dockerfile/distribtest/python_bullseye_x86.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/python_bullseye_x86@sha256:6b0a6c4418e37df9ce3ed664afdf7197093739db9f4f9f05799f55b6ab7e166c",
    "tools/dockerfile/distribtest/python_centos7_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/python_centos7_x64@sha256:13d8f3ae273ac7dab9b5d486ca08045f6ded866c405ed7bb9d2c87574c1b911b",
    "tools/dockerfile/distribtest/python_dev_alpine3.18_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/python_dev_alpine3.18_x64@sha256:85ca50caccad9f37564989c23566f1daec4b9164d9f03095c90d18514f1354c0",
    "tools/dockerfile/distribtest/python_dev_arch_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/python_dev_arch_x64@sha256:b9cf804646fc6ea424f86e5d071372e73b8d1fc8629dece6b9b81237d4228d30",
    "tools/dockerfile/distribtest/python_dev_bullseye_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/python_dev_bullseye_x64@sha256:2c1da4cad1a5c5f825d66881229ec8a92d99941174b7a320d97f5e01cfc3ce8a",
    "tools/dockerfile/distribtest/python_dev_bullseye_x86.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/python_dev_bullseye_x86@sha256:6a781b5064658d63e8eb11cd12f71f0c90b7af2f4e7eb41ccfb07897278349a1",
    "tools/dockerfile/distribtest/python_dev_centos7_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/python_dev_centos7_x64@sha256:e32238c1c46a752881c6c165b918cb24bd182e3957dc72c514fdbd3d5c3312ab",
    "tools/dockerfile/distribtest/python_dev_fedora39_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/python_dev_fedora39_x64@sha256:6fb8eab33a1dcf79a0b9bcec8d1e519c3c37a8dbef59d056c0e8a8895e643a02",
    "tools/dockerfile/distribtest/python_dev_ubuntu2004_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/python_dev_ubuntu2004_x64@sha256:93aa31c1b7599a76b78a3e255ade1760bc41b1e851abd900fc3a2cf301e8a14f",
    "tools/dockerfile/distribtest/python_dev_ubuntu2204_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/python_dev_ubuntu2204_x64@sha256:46065078c896d6a0df383015a809048ff996791b327821bbc78d79835b39b27f",
    "tools/dockerfile/distribtest/python_fedora39_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/python_fedora39_x64@sha256:901152df2a30105797c23f1bdc7364a58f89f1524aca49a9e521671121e7504e",
    "tools/dockerfile/distribtest/python_opensuse_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/python_opensuse_x64@sha256:c06efa1964d268c60eeb14d82e26bc6691f22a4888bbfe921b1e9df4519821af",
    "tools/dockerfile/distribtest/python_python39_buster_aarch64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/python_python39_buster_aarch64@sha256:081affeaa7c2b4a6f9c2816cfc2dc3ff9704c12dc1c7b16e360ef7bfdfeac1d2",
    "tools/dockerfile/distribtest/python_ubuntu2004_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/python_ubuntu2004_x64@sha256:2a164a0be886d97e5706e848c02ee4e7a66619530deca1f95347f25e124a4d4b",
    "tools/dockerfile/distribtest/python_ubuntu2204_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/python_ubuntu2204_x64@sha256:0b8c6f54f40c4a9f20bad558841c6f43ad75059ba9c63e4a1dc918c6be0d35ee",
    "tools/dockerfile/distribtest/ruby_debian11_x64_ruby_3_0.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/ruby_debian11_x64_ruby_3_0@sha256:beb62617d6640a79a12f445c670aa252e19c45751c934fa9f99be188b830d051",
    "tools/dockerfile/distribtest/ruby_debian11_x64_ruby_3_1.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/ruby_debian11_x64_ruby_3_1@sha256:11347339e57c04866585511dd2de87df483179395869b4754a09724a54c1c77e",
    "tools/dockerfile/distribtest/ruby_debian11_x64_ruby_3_2.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/ruby_debian11_x64_ruby_3_2@sha256:c4eb679928e92f660fc8e8ebfd8c76a5d6b6f22e5b6e875c52fa42b166ab5c55",
    "tools/dockerfile/distribtest/ruby_debian11_x64_ruby_3_3.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/ruby_debian11_x64_ruby_3_3@sha256:7def7f623814dd9439ccb33ff0400bae9763bee7b9334c6542884ff240070c83",
    "tools/dockerfile/distribtest/ruby_debian11_x64_ruby_3_4.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/ruby_debian11_x64_ruby_3_4@sha256:208fadc38e1e279fae7e338841ce147088150d0f141d2961f5527bd6ea09b711",
    "tools/dockerfile/distribtest/ruby_ubuntu2004_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/ruby_ubuntu2004_x64@sha256:1a3f814eb4cb7fefa50ee0f4d6d8e62a30bf08201c6e98a09a4b46762b876ec5",
    "tools/dockerfile/distribtest/ruby_ubuntu2204_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/ruby_ubuntu2204_x64@sha256:fc761804f2503ae4a23d6e39b6fec1c43242bbfe5a218cbd6238b0e7b3973ecf",
    "tools/dockerfile/grpc_artifact_manylinux2014_aarch64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_artifact_manylinux2014_aarch64@sha256:9d6f150da39d1b16269d601010876d3f8a2138121db289abad40fdaf7fad287b",
    "tools/dockerfile/grpc_artifact_manylinux2014_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_artifact_manylinux2014_x64@sha256:6e49c8d217eb24732367251c0cdfb438fbde86b4262fb27293bc25ae192bc48f",
    "tools/dockerfile/grpc_artifact_manylinux2014_x86.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_artifact_manylinux2014_x86@sha256:a51c6a5507c21bd1228fb87f66034ae43d6960b22313e4f4637fe4505f2b438a",
    "tools/dockerfile/grpc_artifact_python_linux_armv7.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_artifact_python_linux_armv7@sha256:e66e03d7d8ccc030ac8ac6b75ab63d09231f6a92de4124816dd9743af1dfcef8",
    "tools/dockerfile/grpc_artifact_python_manylinux2014_aarch64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_artifact_python_manylinux2014_aarch64@sha256:d260a5386b894184bf3b6980a57107a7701e7c6a78ee0b8389740af941b130e5",
    "tools/dockerfile/grpc_artifact_python_manylinux2014_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_artifact_python_manylinux2014_x64@sha256:f4acf4965cfb35d7b1e9af7de11b773cf7cf7187d2c4ca941c1459345edc1469",
    "tools/dockerfile/grpc_artifact_python_manylinux2014_x86.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_artifact_python_manylinux2014_x86@sha256:d9a0463da2fb8dcd145465c661a86420c94e6b35f6d1d3cee887c0c21cd5b0ef",
    "tools/dockerfile/grpc_artifact_python_musllinux_1_1_aarch64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_artifact_python_musllinux_1_1_aarch64@sha256:e14d77c766bf35c0f22722cdedac5f03e4e79f6f4e168faf0aeafdd279fd3f47",
    "tools/dockerfile/grpc_artifact_python_musllinux_1_1_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_artifact_python_musllinux_1_1_x64@sha256:30d76d87ca2875d47026049b100e90a0f90385cba8d1f7ff1df66102673578b6",
    "tools/dockerfile/grpc_artifact_python_musllinux_1_1_x86.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_artifact_python_musllinux_1_1_x86@sha256:932b24d3e987fc38c55acdfc8dfd397650d9424ff95f4a64fbf268dc2e21e7b9",
    "tools/dockerfile/interoptest/grpc_interop_aspnetcore.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_interop_aspnetcore@sha256:8e2e732e78724a8382c340dca72e7653c5f82c251a3110fa2874cc00ba538878",
    "tools/dockerfile/interoptest/grpc_interop_cxx.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_interop_cxx@sha256:e5986002b893d5b523a6fc76d0c260ec8ac69110a7e6862361e74b8c6ab11308",
    "tools/dockerfile/interoptest/grpc_interop_dart.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_interop_dart@sha256:0a9b335b3f26083f52037717182a09e54675bbaa5e7aa813b2b3217cbcf53a65",
    "tools/dockerfile/interoptest/grpc_interop_go.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_interop_go@sha256:854dd5be50c10b44a60100491c07bef375faebf20c7e1e037a5bf0a112006759",
    "tools/dockerfile/interoptest/grpc_interop_go1.11.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_interop_go1.11@sha256:ec6d9e27e6bcd277c5fc3f723834e74ca9a966583ba05b234ae49205b509681d",
    "tools/dockerfile/interoptest/grpc_interop_go1.16.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_interop_go1.16@sha256:eb467042572bb6aac596999272172fbf856d63b7e0589f30efd2ff1191eec215",
    "tools/dockerfile/interoptest/grpc_interop_go1.19.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_interop_go1.19@sha256:8ab416ef05883ab849a84df911415754a2925196d8c545c84929dcffa7195b66",
    "tools/dockerfile/interoptest/grpc_interop_go1.8.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_interop_go1.8@sha256:7830a301b37539252c592b9cd7fa30a6142d0afc717a05fc8d2b82c74fb45efe",
    "tools/dockerfile/interoptest/grpc_interop_go1.x.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_interop_go1.x@sha256:854dd5be50c10b44a60100491c07bef375faebf20c7e1e037a5bf0a112006759",
    "tools/dockerfile/interoptest/grpc_interop_http2.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_interop_http2@sha256:574cbe47dc51ccaa10e152ead0a8800b87640aa64d634e33019ebd3d182070a0",
    "tools/dockerfile/interoptest/grpc_interop_java.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_interop_java@sha256:91ff5d28c2de63eaf6ee121429e7a7b269c83110833a5e2a9a46a2954dcbfb4a",
    "tools/dockerfile/interoptest/grpc_interop_node.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_interop_node@sha256:290e4d95f83018bc10fc312885328fa63acd27ef2cbd1f211757846083a67722",
    "tools/dockerfile/interoptest/grpc_interop_nodepurejs.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_interop_nodepurejs@sha256:b990c14434ed85caede949170c2f917085166874de34410be2452b9447e42371",
    "tools/dockerfile/interoptest/grpc_interop_php7.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_interop_php7@sha256:9c04f4eaef43f102079fb688e209246538af86e04388dc2746604b178c86a5df",
    "tools/dockerfile/interoptest/grpc_interop_python.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_interop_python@sha256:d48c1675f3f2cc63edf12e15ad4f9fa18f8c1497495f1bb9b503f851f5072111",
    "tools/dockerfile/interoptest/grpc_interop_pythonasyncio.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_interop_pythonasyncio@sha256:512a0a9a37ca6cc7f3481fd4fea3c879a311718ae96b84b6c3bcb7e0c436652b",
    "tools/dockerfile/interoptest/grpc_interop_ruby.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_interop_ruby@sha256:e6bc549cd454fcd792fd4f1dcf01d754702351861f8b5fa4a353822030597f04",
    "tools/dockerfile/interoptest/lb_interop_fake_servers.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/lb_interop_fake_servers@sha256:ba4c19a2b8e4af7a2d112ef65e6475fb44394cadb2fe17d6f0d434c5b1849bed",
    "tools/dockerfile/test/android_ndk.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/android_ndk@sha256:0fbcafb56036b03148e7cc8f5e492e64b928935d65084018d70bed9e87dd670e",
    "tools/dockerfile/test/bazel.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/bazel@sha256:67b3203cbb0954c85a13cf58b9956ba9a82f23c8522eb195b7da4d3986b0e6c5",
    "tools/dockerfile/test/bazel_arm64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/bazel_arm64@sha256:a5b84a1c6845fb6a9f2816a36d305b56dba46a6db56cb1d537aadd989e71b773",
    "tools/dockerfile/test/csharp_debian11_arm64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/csharp_debian11_arm64@sha256:3fa024a26153906d0cb66dee8b7cd307cb007d0e04a58c3b034b58439c3d3398",
    "tools/dockerfile/test/csharp_debian11_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/csharp_debian11_x64@sha256:e2a9c6fc2f0861e79a75aa86922320ff6e080ba85af23f62c46c758c67c93ea1",
    "tools/dockerfile/test/cxx_alpine_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/cxx_alpine_x64@sha256:7a71386028a9f003d5c73e39c523e5e78e1145e299319b6ebc3f476d3bd21e3a",
    "tools/dockerfile/test/cxx_clang_19_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/cxx_clang_19_x64@sha256:5d34085443033f54fd0fd6e7711fe87522cc3d2da79cf635499b5c4b81b63b94",
    "tools/dockerfile/test/cxx_clang_7_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/cxx_clang_7_x64@sha256:029fc0f9d942fcbd07fb64df75e831c27b937ba99975c3cd88e804873dab5ab7",
    "tools/dockerfile/test/cxx_debian11_openssl102_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/cxx_debian11_openssl102_x64@sha256:a7e480c98678860bdfe608495737c8476d14920ef4ec8d06fe8b0226ab4b261c",
    "tools/dockerfile/test/cxx_debian11_openssl111_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/cxx_debian11_openssl111_x64@sha256:341f1a9d4a349ce880f3613dd931f48a3de9bf135710c51e9182b0fb262040a7",
    "tools/dockerfile/test/cxx_debian11_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/cxx_debian11_x64@sha256:246520a5c0267ab36b876a688a35d007e4d111a05941b22d672161be5ec19dd6",
    "tools/dockerfile/test/cxx_debian11_x86.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/cxx_debian11_x86@sha256:cc404c8bbb60cc0956d004811ee9fbe68ee308df3e991f12b012b36880a0b831",
    "tools/dockerfile/test/cxx_debian12_openssl309_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/cxx_debian12_openssl309_x64@sha256:f57dbd2d9075b9c75bfc6ecb82914523bdc609e7070b713cc8f5d0e2c94de38a",
    "tools/dockerfile/test/cxx_gcc_14_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/cxx_gcc_14_x64@sha256:9cdace85f9e27b232756fa565ff5108f0182c3086642a9ef98b2a29f23b3f02a",
    "tools/dockerfile/test/cxx_gcc_7_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/cxx_gcc_7_x64@sha256:7e2eff34ce0bcd05e39fa5b69fc4cd6e8fbf5e5b78d95ee7949e0df340d276da",
    "tools/dockerfile/test/cxx_gcc_8_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/cxx_gcc_8_x64@sha256:3d4bcff016858a4637ae34d89088e463c16b6e8047c951d909d90ee939c7ea3a",
    "tools/dockerfile/test/php8_debian12_arm64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/php8_debian12_arm64@sha256:b6111d2e6f7addf605322ffafd342f4c72e40e0a6ea4f437683e09d0b921f57f",
    "tools/dockerfile/test/php8_debian12_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/php8_debian12_x64@sha256:c39a84e5b275c9cf9ab7af558460e1edff62ae426bc8d31ef85cd4c21cf8a923",
    "tools/dockerfile/test/php8_zts_debian12_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/php8_zts_debian12_x64@sha256:3497f75483612a447d9b460ac94443b2be0b467232cdd7b8cef0965f7c3d688c",
    "tools/dockerfile/test/python_alpine_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/python_alpine_x64@sha256:1c9bfcd3806716f7e10f2452605443b6deb222247b39228f9db03e88548a251c",
    "tools/dockerfile/test/python_debian11_default_arm64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/python_debian11_default_arm64@sha256:093ec87288ac3ca00f9f9f10145ccf53135ad231e6b6afb660c654b15e232fcb",
    "tools/dockerfile/test/python_debian11_default_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/python_debian11_default_x64@sha256:85512b2679ac040dbe1023eece24b71f22b34a7c630aedf814183f48b1bdb145",
    "tools/dockerfile/test/rbe_ubuntu2004.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/rbe_ubuntu2004@sha256:bce8453713efcff3f4effe0d7bb0ef743ec4e772c63bac637c38d0af0e1a9ad9",
    "tools/dockerfile/test/ruby_debian11_arm64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/ruby_debian11_arm64@sha256:d5d679c0c8475ec790afb6b0d09532c199293589a0d84bf5e3950eef96bdb353",
    "tools/dockerfile/test/ruby_debian11_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/ruby_debian11_x64@sha256:780ccbee31da3ad89859ff3ffa6548b908f1efe873df248af7a1dc41df1a5167",
    "tools/dockerfile/test/sanity.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/sanity@sha256:da094c7a2020e82a42bbd88becc55a664da9ecf29a63b63ec9ec28e59e49e7d2",
}

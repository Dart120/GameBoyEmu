#!/bin/sh
# conan profile new default --detect
# conan profile update settings.compiler.libcxx=libstdc++ default
export CONAN_SYSREQUIRES_MODE=enabled
# apt install -y pkg-config
# apt install -y cmake
conan install . --output-folder=build --build=missing -g CMakeToolchain
# https://bugs.gentoo.org/827889
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=build/conan_toolchain.cmake
cmake --build build

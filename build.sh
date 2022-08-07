#!/bin/sh
conan profile new default --detect
conan profile update settings.compiler.libcxx=libstdc++11 default
export CONAN_SYSREQUIRES_MODE=enabled
apt install -y pkg-config
apt install -y cmake
conan install . --build=missing -c tools.system.package_manager:mode=install
cmake .
make

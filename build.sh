#!/bin/sh
conan profile update settings.compiler.libcxx=libstdc++11 default
export CONAN_SYSREQUIRES_MODE=enabled
apt install pkg-config
apt install cmake
conan install . --build=missing -c tools.system.package_manager:mode=install
cmake .
make

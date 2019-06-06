#!/bin/bash
sudo apt-get update
sudo apt-get install gcc
sudo apt-get install g++
sudo apt-get install git
sudo apt-get install make
sudo apt-get install cmake
git clone https://github.com/microsoft/vcpkg.git
vcpkg/bootstrap-vcpkg.sh
vcpkg/vcpkg install gtest
vcpkg/vcpkg install benchmark
vcpkg/vcpkg integrate install
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=../vcpkg/scripts/buildsystems/vcpkg.cmake -DENABLE_UNIT_TESTS=ON -DENABLE_BENCHMARKS=ON

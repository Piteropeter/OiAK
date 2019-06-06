cmake_minimum_required (VERSION 3.1)

set(APPLICATION_NAME benchmarks)

message(STATUS "Configuring ${APPLICATION_NAME}")

find_package(benchmark CONFIG REQUIRED)
include_directories(${CMAKE_SOURCE_DIR}/src)
add_executable(${APPLICATION_NAME} benchmark.cpp big_integer_benchmark.hpp big_float_benchmark.hpp)
target_link_libraries(${APPLICATION_NAME} oiak_lib benchmark::benchmark benchmark::benchmark_main)

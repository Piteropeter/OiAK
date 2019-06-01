cmake_minimum_required (VERSION 3.4)

set(CMAKE_CXX_STANDARD 14)
set(ENABLE_UNIT_TESTS CACHE BOOL ON)
set(ENABLE_BENCHMARKS CACHE BOOL ON)

project ("OiAK")

add_subdirectory("src")

if(ENABLE_UNIT_TESTS)
add_subdirectory("ut")
endif(ENABLE_UNIT_TESTS)

if(ENABLE_BENCHMARKS)
add_subdirectory("benchmark")
endif(ENABLE_BENCHMARKS)
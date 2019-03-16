cmake_minimum_required (VERSION 3.4)

project ("OiAK")

set(ENABLE_UNIT_TESTS CACHE BOOL ON)
set(CMAKE_CXX_STANDARD 14)

add_subdirectory("src")

if(ENABLE_UNIT_TESTS)
add_subdirectory("ut")
endif(ENABLE_UNIT_TESTS)

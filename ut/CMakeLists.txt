﻿cmake_minimum_required (VERSION 3.1)

set(APPLICATION_NAME unit_tests)

message(STATUS "Configuring ${APPLICATION_NAME}")

enable_testing()
find_package(GTest MODULE REQUIRED)
include_directories(${CMAKE_SOURCE_DIR}/src ${GTEST_INCLUDE_DIR})
add_executable(${APPLICATION_NAME} big_integer_constructor_tests.cpp big_integer_operator_tests.cpp big_integer_other_tests.cpp big_float_constructor_tests.cpp big_float_operator_tests.cpp big_float_other_tests.cpp)
target_link_libraries(${APPLICATION_NAME} oiak_lib GTest::GTest GTest::Main)

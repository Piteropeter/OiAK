cmake_minimum_required (VERSION 3.1)

set(APPLICATION_NAME unit_tests)

message(STATUS "Configuring ${APPLICATION_NAME}")

enable_testing()
find_package(gtest REQUIRED)
include_directories(${CMAKE_SOURCE_DIR}/src ${GTEST_INCLUDE_DIR})
add_executable(${APPLICATION_NAME} big_ineger_tests.cpp)
target_link_libraries(${APPLICATION_NAME} ${LIBRARY_NAME} ${GTEST_BOTH_LIBRARIES})

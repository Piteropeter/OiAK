cmake_minimum_required (VERSION 3.1)

set(APPLICATION_NAME unit_tests)

message(STATUS "Configuring ${APPLICATION_NAME}")

enable_testing()
find_package(gtest REQUIRED)
include_directories(${CMAKE_SOURCE_DIR}/src ${GTEST_INCLUDE_DIR})
#add_executable(Unit_tests "x.cpp")
#target_link_libraries(Unit_tests ${LIBRARY_NAME} ${GTEST_BOTH_LIBRARIES})

#add_test(Unit_tests)
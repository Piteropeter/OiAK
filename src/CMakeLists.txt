cmake_minimum_required (VERSION 3.4)

set(LIBRARY_NAME oiak_lib)

message(STATUS "Configuring ${LIBRARY_NAME}")

add_library(${LIBRARY_NAME} STATIC Lib.cpp Lib.h Utilities.cpp Utilities.h)

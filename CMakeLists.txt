cmake_minimum_required(VERSION 3.0)

cmake_policy(SET CMP0074 NEW)

project(SharedMemory VERSION 1.3 DESCRIPTION "Shared memory wrapper that is based on Boost.")

option(BUILD_EXAMPLE "Build example programs." OFF)
option(BUILD_TEST "Build test program." ON)

if(BUILD_EXAMPLE)
    add_subdirectory(example)
endif()

if(BUILD_TEST)
    add_subdirectory(test)
endif()
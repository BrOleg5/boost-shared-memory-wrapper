cmake_minimum_required(VERSION 3.0)

cmake_policy(SET CMP0074 NEW)

project(SharedMemory VERSION 1.3 DESCRIPTION "Shared memory wrapper that is based on Boost.")

option(BUILD_EXAMPLE "Build example programs." OFF)
option(BUILD_TEST "Build test program." ON)
option(BUILD_DOC "Build documentation" OFF)

if(BUILD_EXAMPLE)
    add_subdirectory(example)
endif()

if(BUILD_TEST)
    add_subdirectory(test)
endif()

if(BUILD_DOC)
    add_subdirectory(doc)
endif()
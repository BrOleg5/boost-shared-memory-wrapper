cmake_minimum_required(VERSION 3.16)

project(shared_memory VERSION 1.0 DESCRIPTION "Shared memory wrapper that is based on boost library.")

add_subdirectory(test)

add_library(shared_memory include/sharedmemory.hpp)

set_target_properties(shared_memory PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(shared_memory PUBLIC
                      ${Boost_LIBRARIES} rt
                      ${Boost_LIBRARIES} pthread )

target_include_directories(shared_memory 
                           PRIVATE "/usr/local/boost_1_77_0"
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
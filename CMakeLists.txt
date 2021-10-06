cmake_minimum_required(VERSION 3.16)

project(shared_memory VERSION 1.0 DESCRIPTION "Shared memory wrapper that is based on boost library.")

add_subdirectory(test)

add_library(shared_memory INTERFACE)

# set_target_properties(shared_memory PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(shared_memory INTERFACE
                      ${Boost_LIBRARIES} rt
                      ${Boost_LIBRARIES} pthread )

target_include_directories(shared_memory 
                           INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include"
                           INTERFACE "/usr/local/boost_1_77_0"
                           )
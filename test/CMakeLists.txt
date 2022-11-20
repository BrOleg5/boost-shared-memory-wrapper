add_executable(shared_memory_test shared_memory_test.cpp)

set_target_properties(shared_memory_test PROPERTIES 
                        PUBLIC_HEADER "${PROJECT_SOURCE_DIR}/include/sharedmemory.hpp")

find_package(Boost 1.71.0 REQUIRED)

if(WIN32)
target_link_libraries(shared_memory_test PUBLIC
                      ${Boost_LIBRARIES})
elseif(UNIX AND NOT APPLE)
target_link_libraries(shared_memory_test PUBLIC
                      ${Boost_LIBRARIES}
                      rt
                      pthread)
endif()

target_include_directories(shared_memory_test PUBLIC 
                            $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                            "${Boost_INCLUDE_DIRS}")
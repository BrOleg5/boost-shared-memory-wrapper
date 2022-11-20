add_executable(transmitter transmitter.cpp)

set_target_properties(transmitter PROPERTIES 
                      PUBLIC_HEADER "${PROJECT_SOURCE_DIR}/include/sharedmemory.hpp")

find_package(Boost 1.71.0 REQUIRED)

if(WIN32)
target_link_libraries(transmitter PUBLIC
                      ${Boost_LIBRARIES})
elseif(LINUX)
target_link_libraries(transmitter PUBLIC
                      ${Boost_LIBRARIES}
                      rt
                      pthread)
endif()

target_include_directories(transmitter PUBLIC 
                           $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                           "${Boost_INCLUDE_DIRS}")

add_executable(receiver receiver.cpp)

set_target_properties(receiver PROPERTIES 
                      PUBLIC_HEADER "${PROJECT_SOURCE_DIR}/include/sharedmemory.hpp")

if(WIN32)
target_link_libraries(receiver PUBLIC
                      ${Boost_LIBRARIES})
elseif(LINUX)
target_link_libraries(receiver PUBLIC
                      ${Boost_LIBRARIES}
                      rt
                      pthread)
endif()

target_include_directories(receiver PUBLIC 
                           $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                           "${Boost_INCLUDE_DIRS}")
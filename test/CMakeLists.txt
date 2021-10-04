add_executable(transmitter transmitter.cpp)
add_executable(receiver receiver.cpp)

target_link_libraries(transmitter PUBLIC shared_memory)

target_include_directories(transmitter
        PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../src")

target_link_libraries(receiver PUBLIC shared_memory)

target_include_directories(receiver
        PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../src")
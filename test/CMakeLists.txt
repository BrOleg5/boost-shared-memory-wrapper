add_executable(transmitter transmitter.cpp)

target_link_libraries(transmitter PUBLIC SharedMemoryLib)

# target_include_directories(transmitter
        # PUBLIC "${SharedMemory_SOURCE_DIR}/include")

if(INSTALL_TESTS)
        install(TARGETS transmitter
                EXPORT SharedMemoryTargets
                RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}/SharedMemoryTest" COMPONENT bin)
endif()

add_executable(receiver receiver.cpp)

target_link_libraries(receiver PUBLIC SharedMemoryLib)

# target_include_directories(receiver
        # PUBLIC "${SharedMemory_SOURCE_DIR}/include")

if(INSTALL_TESTS)
        install(TARGETS receiver
                EXPORT SharedMemoryTargets
                RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}/SharedMemoryTest" COMPONENT bin)
endif()
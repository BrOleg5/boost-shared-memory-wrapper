add_executable(transmitter transmitter.cpp)

# set test dir
if(WIN32 AND NOT CYGWIN)
  set(DEF_BIN_DIR ${CMAKE_INSTALL_BINDIR}/test)
else()
  set(DEF_BIN_DIR ${CMAKE_INSTALL_BINDIR}/SharedMemory/test)
endif()
set(BIN_DIR ${DEF_BIN_DIR} CACHE PATH
  "Installation directory for executable files")

target_link_libraries(transmitter PUBLIC SharedMemoryLib)

# target_include_directories(transmitter
        # PUBLIC "${SharedMemory_SOURCE_DIR}/include")

if(BUILD_TESTS)
        install(TARGETS transmitter
                EXPORT SharedMemoryTargets
                RUNTIME DESTINATION "${BIN_DIR}" COMPONENT bin)
endif()

add_executable(receiver receiver.cpp)

target_link_libraries(receiver PUBLIC SharedMemoryLib)

# target_include_directories(receiver
        # PUBLIC "${SharedMemory_SOURCE_DIR}/include")

if(BUILD_TESTS)
        install(TARGETS receiver
                EXPORT SharedMemoryTargets
                RUNTIME DESTINATION "${BIN_DIR}" COMPONENT bin)
endif()
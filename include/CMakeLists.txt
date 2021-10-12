add_library(SharedMemoryLib INTERFACE)

find_package(Boost 1.71.0 REQUIRED)

target_link_libraries(SharedMemoryLib INTERFACE
                      ${Boost_LIBRARIES} rt
                      ${Boost_LIBRARIES} pthread )

target_include_directories(SharedMemoryLib INTERFACE
                           $<BUILD_INTERFACE:${HEADER_PATH}>
                           $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/SharedMemory>
                           "${Boost_INCLUDE_DIRS}"
                           )

# IMPORTANT: Add the foo library to the "export-set"
install(TARGETS SharedMemoryLib EXPORT SharedMemoryTargets)
install(FILES ${header} DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/SharedMemory")
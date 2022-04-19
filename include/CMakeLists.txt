add_library(SharedMemoryLib INTERFACE)

find_package(Boost 1.71.0 REQUIRED)

# set include dir
if(WIN32 AND NOT CYGWIN)
  set(DEF_INCLUDE_DIR ${CMAKE_INSTALL_INCLUDEDIR})
else()
  set(DEF_INCLUDE_DIR ${CMAKE_INSTALL_INCLUDEDIR}/SharedMemory)
endif()
set(INCLUDE_DIR ${DEF_INCLUDE_DIR} CACHE PATH
  "Installation directory for include files")

if (WIN32 OR MSVC)
    target_link_libraries(SharedMemoryLib INTERFACE
                        ${Boost_LIBRARIES} )
else() #Linux
    target_link_libraries(SharedMemoryLib INTERFACE
                        ${Boost_LIBRARIES}
                        rt
                        pthread )
endif()

target_include_directories(SharedMemoryLib INTERFACE
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
                           $<INSTALL_INTERFACE:${INCLUDE_DIR}>
                           "${Boost_INCLUDE_DIRS}"
                           )

install(TARGETS SharedMemoryLib EXPORT SharedMemoryTargets)
install(FILES sharedmemory.hpp DESTINATION "${INCLUDE_DIR}")
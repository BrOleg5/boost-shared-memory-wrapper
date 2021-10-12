cmake_minimum_required(VERSION 3.0)

cmake_policy(SET CMP0054 NEW)

project(SharedMemory VERSION 1.1 DESCRIPTION "Shared memory wrapper that is based on boost library.")

# set header
set(HEADER_PATH "${SharedMemory_SOURCE_DIR}/include")
set(header ${HEADER_PATH}/sharedmemory.hpp)

# set cmake config install dirs
if(WIN32 AND NOT CYGWIN)
  set(DEF_INSTALL_CMAKE_DIR CMake)
else()
  set(DEF_INSTALL_CMAKE_DIR lib/cmake/SharedMemory)
endif()
set(INSTALL_CMAKE_DIR ${DEF_INSTALL_CMAKE_DIR} CACHE PATH
  "Installation directory for CMake files")


include(GNUInstallDirs)

option(BUILD_TESTS "Build tests programs." OFF)
option(INSTALL_TESTS "Install tests programs." OFF)

add_subdirectory(include)

if(BUILD_TESTS OR INSTALL_TESTS)
  add_subdirectory(test)
endif()

# Add all targets to the build-tree export set
if(BUILD_TESTS)
  export(TARGETS SharedMemoryLib transmitter receiver
         FILE "${PROJECT_BINARY_DIR}/SharedMemoryTargets.cmake")
else()
  export(TARGETS SharedMemoryLib
         FILE "${PROJECT_BINARY_DIR}/SharedMemoryTargets.cmake")
endif()

# Export the package for use from the build-tree
# (this registers the build-tree with a global CMake-registry)
export(PACKAGE SharedMemory)

# Create the SharedMemoryConfig.cmake and SharedMemoryConfigVersion files
# ... for the build tree
set(CONF_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}")
configure_file(SharedMemoryConfig.cmake.in
               "${PROJECT_BINARY_DIR}/SharedMemoryConfig.cmake" @ONLY)
          
# ... for the install tree
set(CONF_INCLUDE_DIRS "\${SHAREDMEMORY_CMAKE_DIR}/${CMAKE_INSTALL_INCLUDEDIR}")
configure_file(SharedMemoryConfig.cmake.in
               "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/SharedMemoryConfig.cmake" @ONLY)
  
# ... for both
configure_file(SharedMemoryConfigVersion.cmake.in "${PROJECT_BINARY_DIR}/SharedMemoryConfigVersion.cmake" @ONLY)

# Install the SharedMemoryConfig.cmake and SharedMemoryConfigVersion files
install(FILES
        "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/SharedMemoryConfig.cmake"
        "${PROJECT_BINARY_DIR}/SharedMemoryConfigVersion.cmake"
        DESTINATION "${INSTALL_CMAKE_DIR}" COMPONENT dev)

# Install the export set for use with the install-tree
install(EXPORT SharedMemoryTargets
        DESTINATION "${INSTALL_CMAKE_DIR}" COMPONENT dev)
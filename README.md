# Boost shared memory

There are boost's shared memory wrapper. Transmitter class is server and Receiver class is client.

This library is header-only (nothing to build). You can simple copy header file from include directory and add to your project.

Wrappers is based on official [Quick Guide for Impatient](https://www.boost.org/doc/libs/1_38_0/doc/html/interprocess/quick_guide.html
), in section **Creating vectors in shared memory**.

## Requirements

- CMake v3.0 or later
- Boost library v1.71.0 or later
- compiler: gcc 9.3.0+ or MSVC 19+ (Visual Studio 2017)

## Configure, build and install project with CMake

### Ubuntu 20.04

```
# Create build directory
mkdir build

# Configure
cmake -S boost-shared-memory-wrapper/ -B build/

# Build certain configuration <cfg>: Debug (default), Release
cmake --build build/ --config <cfg>

# Install certain configuration <cfg>: Debug (default), Release
# <prefix> is installation path (default /usr/local)
sudo cmake --install build/ --config <cfg> --prefix <prefix>
```

### Windows 10

#### x86

```
# Create build directory
mkdir .\build\

# Configure. Build system generator <generator-name>: for MSVC 19 (Visual Studio 2017) is "Visual Studio 15".
# Command "cmake --help" print full lust of generators that are available on your platform
cmake -S .\boost-shared-memory-wrapper\ -B .\build\ -G <generator-name>

# Build certain configuration <cfg>: Debug (default), Release
cmake --build .\build\ --config <cfg>

# Install certain library configuration <cfg>: Debug (default), Release
# <prefix> is installation path (default SystemPartition:\Program Files (x86)\<project name>)
cmake --install .\build\ --config <cfg> --prefix <prefix>
```

#### x64

```
# Create build directory
mkdir .\build\

# Configure. Build system generator <generator-name>: for MSVC 19 (Visual Studio 2017) is "Visual Studio 15 Win64".
# Command "cmake --help" print full lust of generators that are available on your platform
cmake -S .\boost-shared-memory-wrapper\ -B .\build\ -G <generator-name>

# Build certain configuration <cfg>: Debug (default), Release
cmake --build .\build\ --config <cfg>

# Install certain library configuration <cfg>: Debug (default), Release
# <prefix> is installation path (default SystemPartition:\Program Files (x86)\<project name>)
cmake --install .\build\ --config <cfg> --prefix <prefix>
```

### Extra options

You can build and install test programs. For this add option `-D BUILD_TESTS=ON`.
```
# Configure
cmake -S boost-shared-memory-wrapper/ -B build/ -DBUILD_TESTS=ON
```

## Using SharedMemory with CMake

Add this strings in your CMakeLists.txt file:
```
find_package(SharedMemory 1.1 REQUIRED)
target_link_libraries(<ProjectName> SharedMemoryLib)
# if necessary, add include directories to target
target_include_directories(<ProjectName> ${SharedMemory_INCLUDE_DIRS})
```

## Example

First process send data:
```
#include "sharedmemory.hpp"

int main() {
    // Create Transmitter object
    shm::Transmitter<int>  transmitter("SMF", 1000);
    // Insert data in the vector
    for (size_t i = 0; i < 10; i++)
    {
        transmitter.data->push_back((i);
    }

    // Your program to process and send data
    // . . .

    return 0;
}
```

Second process receive data:
```
#include "sharedmemory.hpp"

int main() {
    // Create Receiver object
    shm::Receiver<int>  receiver("SMF");

    // Your program to obtain and process data
    // . . .
    // Access data with method at(): receiver.data->at(i)
    
    return 0;
}
```
# Boost shared memory

There are boost's shared memory wrapper. Transmitter class is server and Receiver class is client.

This library is header-only (there's nothing to build). You can simple copy header file from include directory and add to your project.

Wrappers is based on official [Quick Guide for Impatient](https://www.boost.org/doc/libs/1_38_0/doc/html/interprocess/quick_guide.html
), in section Creating vectors in shared memory.

## Requirements

- CMake v3.0 or later
- Boost library v1.71.0 or later
- gcc 9.3.0+ or MSVC 19+

## Configure, build and install project

### Ubuntu 20.04

```
# Create build directory
mkdir build

# Configure
cmake -S boost-shared-memory-wrapper/ -B build/

# Build
cmake --build build/

# Install
sudo cmake --install build/
```

### Windows 10

Command shell or PowerShell will be run as administrator to install library in system partition.

#### x86

```
# Create build directory
mkdir build

# Configure as static library
cmake -S boost-shared-memory-wrapper/ -B build/ -G "Visual Studio 15"

# Build library
cmake --build build/

# Install library
sudo cmake --install build/
```

#### x64

```
# Create build directory
mkdir build

# Configure as static library
cmake -S boost-shared-memory-wrapper/ -B build/ -G "Visual Studio 15 Win64"

# Build library
cmake --build build/

# Install library
sudo cmake --install build/
```

### Extra options

You can also build and install tests:
```
# Configure
cmake -S boost-shared-memory-wrapper/ -B build/ -DBUILD_TESTS=ON -DINSTALL_TESTS=ON
```

## Using SharedMemory with CMake

Add this strings in your CMakeLists.txt file:
```
find_package(SharedMemory 1.1 REQUIRED)
target_link_libraries(<ProjectName> SharedMemoryLib)
# if nessesary, add include directories to target
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
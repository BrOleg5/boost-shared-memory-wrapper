# Boost shared memory

There are boost's shared memory wrapper. Transmitter class is server and Receiver class is client.

This library is header-only (nothing to build). You can simple copy header file from include directory and add to your project.

Wrappers is based on official [Quick Guide for Impatient](https://www.boost.org/doc/libs/1_38_0/doc/html/interprocess/quick_guide.html
), in section **Creating vectors in shared memory**.

## Requirements

- CMake v3.0 or later
- Boost library v1.71.0 or later
- compiler: gcc 9.3.0+ or MSVC 19+ (Visual Studio 2017)

## Build

```bash
# Create build directory
mkdir build

# Configure
cmake -S boost-shared-memory-wrapper/ -B build/

# Build certain configuration <cfg>: Debug (default), Release
cmake --build build/ --config <cfg>
```

### Extra options

You can build and install test program. For this add option `-D BUILD_TEST=ON`.

```bash
# Configure
cmake -S boost-shared-memory-wrapper/ -B build/ -D BUILD_TESTS=ON
```

Also add `-D BUILD_EXAMPLE=ON` option to build examples programs: transmitter and receiver.

```bash
# Configure
cmake -S boost-shared-memory-wrapper/ -B build/ -D BUILD_EXAMPLE=ON
```

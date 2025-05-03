<img src="assets/logo_upscaled.png" alt="# Hemline Havoc">

A pair of sentient pants has beef with the fashion overlords.


## Building

### CMake
This project is built using CMake. It downloads all of the required libraries and links them to the executable.

If you are building the project for development, here are the commands you need:
```sh
cmake -B build/dev -DCMAKE_BUILD_TYPE=Debug
cmake --build build/dev
```

The release build can be built using the following commands:
```sh
cmake -B build/release -DCMAKE_BUILD_TYPE=Release
cmake --build build/release
```

To generate a distributable ZIP file:
```sh
cd build/release
cpack
```

### Make
There is a Makefile in the repository for Linux users who have SDL3 and SDL3_image installed on their systems. To use it, all you need to do is run:
```sh
make -j$(nproc)
```
This is not recommended as the setup with CMake simplifies a lot of other aspects of the project.

cmake_minimum_required(VERSION 3.20)
project(HemlineHavoc LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set default build type to Release if not specified
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
endif()
set(VALID_BUILD_TYPES Debug Release)
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS ${VALID_BUILD_TYPES})

# Enable FetchContent
include(FetchContent)

# Fetch SDL3
FetchContent_Declare(
  SDL3
  GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
  GIT_TAG main 
)
FetchContent_MakeAvailable(SDL3)

# Fetch SDL3_image
FetchContent_Declare(
  SDL3_image
  GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
  GIT_TAG main
)
FetchContent_MakeAvailable(SDL3_image)

# Source files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

# Executable
add_executable(HemlineHavoc ${SOURCES})

# Link against SDL3 and SDL3_image
target_link_libraries(HemlineHavoc PRIVATE SDL3::SDL3 SDL3_image::SDL3_image)

# Installation for packaging
install(TARGETS HemlineHavoc RUNTIME DESTINATION bin)

# Optional: CPack packaging configuration
include(InstallRequiredSystemLibraries)
set(CPACK_GENERATOR "ZIP") # Change to NSIS, TGZ, DEB, etc. as needed
set(CPACK_PACKAGE_NAME "HemlineHavoc")
set(CPACK_PACKAGE_VERSION "0.1.0")
include(CPack)

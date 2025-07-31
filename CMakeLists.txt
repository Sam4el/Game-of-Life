cmake_minimum_required(VERSION 3.16)
project(gameOfLife)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True) # Don't silently fall back to an older version if C++17 is not available
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add include directories
include_directories(${PROJECT_SOURCE_DIR}/inc)  # Header locations for #include "something.h"

# Add subdirectory
add_subdirectory(src/board) # There is another CMakeLists.txt in this catalog

# Add executable
add_executable(gameOfLife src/main.cpp)  # Build executable from there

# Link modules
target_link_libraries(gameOfLife PRIVATE board)     # Link gameOfLife with board library
                                                    # PRIVATE means only gameOfLife will know about this, not thing that depend on gameOfLife

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

# Only do this for testing
FetchContent_MakeAvailable(googletest)

enable_testing()
add_subdirectory(test/board)
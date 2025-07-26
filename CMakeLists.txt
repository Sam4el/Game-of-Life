cmake_minimum_required(VERSION 3.16)
project(gameOfLife)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add executable
add_executable(gameOfLife src/main.cpp)
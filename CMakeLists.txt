cmake_minimum_required(VERSION 3.0)
project(brighty)

add_executable(brighty src/main.cpp src/device.cpp)

set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")
set_property(TARGET brighty PROPERTY CXX_STANDARD 20)
target_include_directories(
    brighty PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

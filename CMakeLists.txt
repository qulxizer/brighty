cmake_minimum_required(VERSION 4.0)
project(brighty)

add_executable(brighty src/main.cpp src/device.cpp)
set_property(TARGET brighty PROPERTY CXX_STANDARD 20)
target_include_directories(
    brighty PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

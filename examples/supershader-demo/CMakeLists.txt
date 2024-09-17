cmake_minimum_required(VERSION 3.10)

project(supershader-demo)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

link_libraries(SDL3 supernova supershader)

add_executable(${PROJECT_NAME} main.cpp)

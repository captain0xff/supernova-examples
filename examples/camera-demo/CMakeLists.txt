cmake_minimum_required(VERSION 3.10)

project(camera-demo)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (WIN32)
	link_libraries(mingw32 SDL3 supernova)
else ()
	link_libraries(supernova)
endif()

add_executable(${PROJECT_NAME} main.cpp)

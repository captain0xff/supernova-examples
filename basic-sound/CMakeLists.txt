cmake_minimum_required(VERSION 3.0.0)

project(basic-sound)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (WIN32)
	link_libraries(mingw32 SDL2main SDL2 supernova)
else ()
	link_libraries(supernova)
endif()

add_executable(${PROJECT_NAME} main.cpp)

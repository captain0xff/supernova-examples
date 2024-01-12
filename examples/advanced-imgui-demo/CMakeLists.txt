cmake_minimum_required(VERSION 3.10)

project(advanced-imgui-demo)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (WIN32)
	link_libraries(mingw32 SDL2main SDL2 supernova imgui super_gui)
else ()
	link_libraries(supernova imgui super_gui)
endif()

add_executable(${PROJECT_NAME} main.cpp)

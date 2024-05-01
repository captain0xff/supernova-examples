cmake_minimum_required(VERSION 3.10)

project(server-discovery-demo)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (WIN32)
	link_libraries(mingw32)
endif()
link_libraries(SDL3 supernova)

add_executable(server server.cpp)
add_executable(client client.cpp)

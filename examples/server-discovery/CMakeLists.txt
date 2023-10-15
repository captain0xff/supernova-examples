cmake_minimum_required(VERSION 3.10)

project(udp-net-demo)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (WIN32)
	link_libraries(mingw32 SDL2main SDL2 SDL2_image SDL2_mixer SDL2_ttf SDL2_net supernova)
else ()
	link_libraries(SDL2 SDL2_image SDL2_mixer SDL2_ttf SDL2_net supernova)
endif()

add_executable(server server.cpp)
add_executable(client client.cpp)

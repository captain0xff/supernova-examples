cmake_minimum_required(VERSION 3.6)

project(supernova-demos)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(examples/basic-font)
add_subdirectory(examples/basic-sound)
add_subdirectory(examples/fog-of-war)
add_subdirectory(examples/json-demo)
add_subdirectory(examples/basic-imgui-demo)
add_subdirectory(examples/particles-in-a-box)
# add_subdirectory(examples/server-discovery)
add_subdirectory(examples/basic-template)
add_subdirectory(examples/graphics-demo)
add_subdirectory(examples/camera-demo)
add_subdirectory(examples/supershader-demo)
add_subdirectory(examples/datagram-demo)
add_subdirectory(examples/shader-hot-reloader)

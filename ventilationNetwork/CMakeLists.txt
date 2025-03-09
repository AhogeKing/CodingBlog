cmake_minimum_required(VERSION 3.30)
project(ventilationNetwork)

set(CMAKE_CXX_STANDARD 23)

include_directories(${CMAKE_SOURCE_DIR}/inc)

file(GLOB SRC_LIST "src/*.cpp")

add_executable(output ${SRC_LIST})

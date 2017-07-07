cmake_minimum_required(VERSION 3.8)
project(serial_proj C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


file(GLOB headers src/*.h)
file(GLOB sources src/*.cpp)


set(main_SRCS ${sources} ${headers})
add_executable(serial_proj ${main_SRCS})

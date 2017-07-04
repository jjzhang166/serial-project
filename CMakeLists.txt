cmake_minimum_required(VERSION 3.8)
project(serial_proj C CXX)

file(GLOB headers src/*.h)
file(GLOB sources src/*.cpp)


set(main_SRCS ${sources} ${headers})
add_executable(serial_proj ${main_SRCS})
cmake_minimum_required(VERSION 3.15)
project(BigBool C)

set(CMAKE_C_STANDARD 99)

add_library(BigBool big_bool.c big_bool.h)
add_executable(test test.c)

target_link_libraries(test BigBool)
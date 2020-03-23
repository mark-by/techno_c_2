cmake_minimum_required(VERSION 3.6)

project(count_symbols)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lm -Wall -Werror -O0 -ggdb ")

add_subdirectory(src)

enable_testing()
add_subdirectory(test)


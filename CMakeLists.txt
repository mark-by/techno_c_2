cmake_minimum_required(VERSION 3.6)

project(count_symbols)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lm -Wall -Werror -O0 -ggdb ")

configure_file(CMakeLists.txt.in
        googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
        ${CMAKE_BINARY_DIR}/googletest-build)

add_subdirectory(src)

enable_testing()
add_subdirectory(test)


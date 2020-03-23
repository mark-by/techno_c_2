cmake_minimum_required(VERSION 3.6)

project(count_symbols)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lm -Wall -Werror -O0 -ggdb ")
#GTEST
#configure_file(CMakeLists.txt.in
#    googletest-download/CMakeLists.txt)
#execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
#    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)
#execute_process(COMMAND ${CMAKE_COMMAND} --build .
#    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)
#add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
#    ${CMAKE_BINARY_DIR}/googletest-build)
#
#enable_testing()
#add_subdirectory(test)

#Project build settings
include_directories("${PROJECT_SOURCE_DIR}/include")
link_directories("${PROJECT_SOURCE_DIR}/include")

set(COMMON_LIB_SOURCE_FILES
        "${PROJECT_SOURCE_DIR}/src/count_symbols.c")

set(STATIC_LIB_SOURCE_FILES
        "${COMMON_LIB_SOURCE_FILES}"
        "${PROJECT_SOURCE_DIR}/src/count_symbols_single_proc.c")

set(SHARED_LIB_SOURCE_FILES
        "${COMMON_LIB_SOURCE_FILES}"
        "${PROJECT_SOURCE_DIR}/src/count_symbols_multiple_proc.c")

add_library(count_symbols_lib STATIC ${STATIC_LIB_SOURCE_FILES})
add_library(count_symbols_lib_s SHARED ${SHARED_LIB_SOURCE_FILES})

add_executable(count_symbols__single_process ${PROJECT_SOURCE_DIR}/src/main.c)
add_executable(count_symbols__multiple_processes ${PROJECT_SOURCE_DIR}/src/main.c)

target_link_libraries(count_symbols__single_process count_symbols_lib -lm)
target_link_libraries(count_symbols__multiple_processes count_symbols_lib_s -lm)

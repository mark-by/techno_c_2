include_directories("${PROJECT_SOURCE_DIR}/include")

set(COMMON_LIB_SOURCE_FILES
        count_symbols.c
        )

set(STATIC_LIB_SOURCE_FILES
        ${COMMON_LIB_SOURCE_FILES}
        count_symbols_single_proc.c
        )

set(SHARED_LIB_SOURCE_FILES
        ${COMMON_LIB_SOURCE_FILES}
        count_symbols_multiple_proc.c
        )

add_library(count_symbols_lib STATIC ${STATIC_LIB_SOURCE_FILES})
add_library(count_symbols_lib_s SHARED ${SHARED_LIB_SOURCE_FILES})

add_executable(count_symbols__single_process main.c)
add_executable(count_symbols__multiple_processes main.c)

target_link_libraries(count_symbols__single_process count_symbols_lib -lm)
target_link_libraries(count_symbols__multiple_processes count_symbols_lib_s -lm)

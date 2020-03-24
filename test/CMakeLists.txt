find_package(Threads REQUIRED)

include_directories("${PROJECT_SOURCE_DIR}/include")

file(GLOB tests
        count_symbols.cpp
        main.cpp
        )

add_executable(run_tests
        ${tests}
        )
add_executable(run_tests_s
        ${tests}
        )

target_link_libraries(run_tests
        count_symbols_lib
        gtest_main
        pthread
        )

target_link_libraries(run_tests_s
        count_symbols_lib_s
        gtest_main
        pthread
        )

add_test(NAME run_tests
        COMMAND run_tests)

add_test(NAME run_tests_s
        COMMAND run_tests_s)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories("${PROJECT_SOURCE_DIR}/include")

file(GLOB tests
        count_symbols.cpp
        )

add_executable(run_tests
        ${tests}
        main.cpp
        )
add_executable(run_tests_s
        ${tests}
        main.cpp)

target_link_libraries(run_tests
        count_symbols_lib
        ${GTEST_LIBRARIES}
        pthread
        )

target_link_libraries(run_tests_s
        count_symbols_lib_s
        ${GTEST_LIBRARIES}
        pthread
        )

add_test(NAME run_tests
        COMMAND run_tests)

add_test(NAME run_tests_s
        COMMAND run_tests_s)

include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
        Three-dimensional-array_test
        Three-dimensional-array_test.cpp
)

target_link_libraries(
        Three-dimensional-array_test
        ternary_massive
        GTest::gtest_main
)

target_include_directories(Three-dimensional-array_test PUBLIC ${PROJECT_SOURCE_DIR})

include(GoogleTest)

gtest_discover_tests(Three-dimensional-array_test)
cmake_minimum_required(VERSION 3.14)
project(tetravex-solver)

set(CMAKE_CXX_STANDARD 17)
add_executable(
        tetra-solver
        main.cc
        tetravex.cc
        io.cc
        solver.cc
        tests_generation/generate.cc)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


#set(CMAKE_CXX_FLAGS_RELEASE "-O2")

enable_testing()

add_executable(
        tests
        tests_generation/test.cc
        solver.cc
        tests_generation/generate.cc
        tetravex.cc
)
target_link_libraries(
        tests
        gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)
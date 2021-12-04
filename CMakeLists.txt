
project(tetravex-solver)

set(CMAKE_CXX_STANDARD 17)
add_executable(tetra-solver main.cc tetravex.cc io.cc solver.cc generate.cc)
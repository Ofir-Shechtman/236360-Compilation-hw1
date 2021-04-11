cmake_minimum_required(VERSION 3.13)
project(hw1)

# set(GCC_COVERAGE_COMPILE_FLAGS "")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

add_executable(hw1 lex.yy.c part_a.cpp)
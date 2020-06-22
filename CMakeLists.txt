cmake_minimum_required(VERSION 3.9)
project(DoYouWantToCmyAlgorithms_ C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Werror -O3")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

include_directories(include)

file(GLOB sources algorithms/maze_generator_recursive_backtracking.c)
add_executable(DoYouWantToCmyAlgorithms_ ${sources} main.c)

add_executable(generator ${sources} generate.c)
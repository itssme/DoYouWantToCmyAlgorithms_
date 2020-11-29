cmake_minimum_required(VERSION 3.9)
project(geneticMaze C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Werror -O3")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

#add_definitions(-DINFO)

include_directories(include)
file(GLOB sources src/maze_generator_backtracking.c src/heap.c)
add_executable(geneticMaze ${sources} main.c)
target_link_libraries(geneticMaze m)
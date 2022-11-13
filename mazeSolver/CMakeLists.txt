cmake_minimum_required(VERSION 3.9)
project(mazeSolving C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_BUILD_TYPE Release)

#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic -Werror -O3")
#set(CMAKE_C_FLAGS_RELEASE "-O3")

add_compile_options("-O3")

#add_definitions(-DINFO)
#add_definitions(-DVISUALIZE)

include_directories(include)
file(GLOB sources src/heap.c src/maze.c src/random.c)

add_executable(geneticMaze ${sources} geneticMazeGenerator.c)
target_link_libraries(geneticMaze m)

add_executable(solver ${sources} solve.c)

get_directory_property(DEFS COMPILE_DEFINITIONS)
if (DEFS MATCHES "^VISUALIZE")
    MESSAGE(STATUS "Visualization is set to true, will link with curses" )
    target_link_libraries(solver ncurses)
    target_link_libraries(geneticMaze ncurses)
endif ()

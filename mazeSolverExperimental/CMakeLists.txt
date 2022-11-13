cmake_minimum_required(VERSION 3.9)
project(mazeSolving C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_BUILD_TYPE Release)

add_compile_options("-Wall")
add_compile_options("-Wextra")
add_compile_options("-pedantic")
add_compile_options("-Werror")
add_compile_options("-O3")

#add_definitions(-DINFO)
#add_definitions(-DVISUALIZE)

include_directories(include)
file(GLOB sources src/queue.c src/maze.c)

add_executable(solver ${sources} solve.c)

get_directory_property(DEFS COMPILE_DEFINITIONS)
if (DEFS MATCHES "^VISUALIZE")
    MESSAGE(STATUS "Visualization is set to true, will link with curses" )
    target_link_libraries(solver ncurses)
endif ()
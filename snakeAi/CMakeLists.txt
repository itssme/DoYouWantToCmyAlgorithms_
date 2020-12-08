cmake_minimum_required(VERSION 3.9)
project(snakeAi)

set(CMAKE_CXX_STANDARD 20)

# link libraries
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lm -lncurses  -ltinfo -pthread")

# set warnings
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -pedantic")

include_directories(include)

file(GLOB sources src/game.cpp src/visualized_game.cpp)
add_executable(brain ${sources} brain.cpp)
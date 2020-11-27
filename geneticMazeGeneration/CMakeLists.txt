cmake_minimum_required(VERSION 3.14)
project(geneticMazeGeneration)

set(CMAKE_CXX_STANDARD 17)

add_executable(geneticMazeGeneration main.cpp src/astar.cpp)
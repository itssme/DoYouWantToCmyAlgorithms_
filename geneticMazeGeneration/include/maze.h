#ifndef GENETICMAZE_MAZE_H
#define GENETICMAZE_MAZE_H

#include "types.h"
#include "heap.h"

typedef struct Maze {
    snumber height;
    snumber width;
    char* data;
} Maze;

Maze* newMaze(snumber width, snumber height);
void freeMaze(Maze** maze);
void printMaze(Maze* maze);
snumber solve(Maze* maze, Heap* heap);
char getContent(Maze* maze, snumber x, snumber y);
void resetMaze(Maze* maze);

#endif
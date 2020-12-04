#ifndef GENETICMAZE_MAZE_H
#define GENETICMAZE_MAZE_H

#ifdef VISUALIZE

#include <ncurses.h>
#include <unistd.h>

WINDOW* window;
bool setup;
#endif

#include "queue.h"

typedef enum FieldState {
    EMPTY = 0,
    WALL = 1,
    NEWLINE = 2,
    PATH = 3,
    EXPLORED = 4
#ifdef VISUALIZE
    , EXPLORING = 5
#endif
} FieldState;

typedef struct Maze {
    int height;
    int width;
    char* data;
} Maze;

Maze* newMaze(int width, int height);

void freeMaze(Maze** maze);

void printMaze(Maze* maze);

int solve(Maze* maze, Queue* queue);

char getContent(Maze* maze, int index);

void setContent(Maze* maze, int index, FieldState state);

#ifdef VISUALIZE

void setContentCurses(int x, int y, enum FieldState state);

#endif

#endif
#ifndef GENETICMAZE_MAZE_H
#define GENETICMAZE_MAZE_H

#ifdef VISUALIZE

#include <ncurses.h>
#include <unistd.h>

extern WINDOW* window;
extern bool setup;
#endif

#include "types.h"
#include "heap.h"

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

typedef struct BackPoint {
    snumber x;
    snumber y;
    snumber baseCost;
    snumber predIndex;
} BackPoint;

typedef struct Maze {
    snumber height;
    snumber width;
    snumber backIdx;
    BackPoint* back;
    char* data;

} Maze;

Maze* newMaze(snumber width, snumber height);

void freeMaze(Maze** maze);

void printMaze(Maze* maze);

snumber solve(Maze* maze, Heap* heap);

char getContent(Maze* maze, snumber x, snumber y);

void setContent(Maze* maze, snumber x, snumber y, FieldState state);

void resetMaze(Maze* maze);

#ifdef VISUALIZE

void setContentCurses(snumber x, snumber y, enum FieldState state);

#endif

#endif
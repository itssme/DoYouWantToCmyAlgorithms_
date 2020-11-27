#include <iostream>
#include <cstring>
#include "src/astar.cpp"


char** mazeAlloc() {
    char** maze = (char**) malloc(sizeof(char*) * HEIGHT);

    for (int i = 0; i < HEIGHT; i++) {
        maze[i] = (char*) malloc((sizeof(char) * WIDTH) + 1);
    }

    return maze;
}

char** mazeCalloc() {
    char** maze = (char**) malloc(sizeof(char*) * HEIGHT);
    for (int i = 0; i < HEIGHT; i++) {
        maze[i] = (char*) malloc((sizeof(char) * WIDTH) + 1);
        maze[i][0] = '#';
        for (int j = 1; j < WIDTH - 1; j++) {
            maze[i][j] = '.';
        }
        maze[i][WIDTH] = '\0';
    }

    for (int i = 0; i < HEIGHT; i++) {
        maze[i][0] = '#';
        maze[i][WIDTH - 1] = '#';
    }

    for (int i = 0; i < WIDTH - 1; i++) {
        maze[0][i] = '#';
        maze[HEIGHT - 1][i] = '#';
    }

    return maze;
}

void mazeCopy(char** src, char** dest) {
    for (int i = 0; i < HEIGHT; ++i) {
        memcpy(dest[i], src[i], (sizeof(char) * WIDTH) + 1);
    }
}

void printMaze(char** maze) {
    for (int i = 0; i < HEIGHT; i++) {
        puts(maze[i]);
    }
}

void free(char** maze) {
    for (int i = 0; i < HEIGHT; i++) {
        free(maze[i]);
    }
    free(maze);
}

int main() {
    char** maze = mazeCalloc();
    char** maze2 = mazeAlloc();

    printMaze(maze);

    Solver sol = Solver(maze);
    sol.solve();

    free(maze);
    free(maze2);

    return 0;
}

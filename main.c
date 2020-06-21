#include <stdio.h>
#include <stdlib.h>
#include <zconf.h>
#include <time.h>

#include "types.h"
#include "maze_generator_recursive_backtracking.h"

#define GENERATE_MAZE 1

#define MAZE_SIZE_H 10000
#define MAZE_SIZE_W 10000

int main() {
    clock_t begin = clock();

    for (int i = 0; i < GENERATE_MAZE; ++i) {
        srand(i);
        char** maze = generate_maze(MAZE_SIZE_H, MAZE_SIZE_W);

        // free memory used by maze
        for (uint j = 0; j < MAZE_SIZE_H; j++ ) {
            free(maze[j]);
        }
        free(maze);
    }

    clock_t end = clock();
    double elapsed_secs = (double) (end - begin) / CLOCKS_PER_SEC;

    printf("generated %d (%dx%d) mazes in %f seconds", GENERATE_MAZE, MAZE_SIZE_H, MAZE_SIZE_W, elapsed_secs);

    return 0;
}
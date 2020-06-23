#include <stdio.h>
#include <stdlib.h>
#include <zconf.h>
#include <time.h>

#include "types.h"
#include "maze_generator_recursive_backtracking.h"

#define GENERATE_MAZE 1


int main(int argc, char *argv[]) {
    uint height = strtoul(argv[1], NULL, 10);
    uint width = strtoul(argv[2], NULL, 10);

    clock_t begin = clock();

    //srand(begin);
    char* maze = generate_maze(height, width);

    clock_t end = clock();
    double elapsed_secs = (double) (end - begin) / CLOCKS_PER_SEC;

    printf("generated %d (%dx%d) mazes in %f seconds\n", GENERATE_MAZE, height, width, elapsed_secs);
    //print_maze(maze, height + 1);

    free(maze);

    return 0;
}
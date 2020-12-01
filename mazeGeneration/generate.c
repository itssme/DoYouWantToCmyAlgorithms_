#include <stdio.h>
#include <stdlib.h>
#include <zconf.h>
#include <time.h>

#include "types.h"
#include "maze_generator_backtracking.h"


int main(int argc, char* argv[]) {
    if (argc != 3 && argc != 4) {
        printf("Usage: ./generator <height> <width> [random] > maze.txt\n"
               "If the third parameter [random] is set the random number generator will\n"
               "be initialized with the current time. (Just provide something as 3rd param)");
        return 1;
    }

    uint height = strtoul(argv[1], NULL, 10);
    uint width = strtoul(argv[2], NULL, 10);

    if (argc == 4) {
        srand(clock());
    }

#ifdef BENCH
    clock_t begin = clock();
#endif

    char* maze = generate_maze(height, width);

#ifdef BENCH
    clock_t end = clock();
    double elapsed_secs = (double) (end - begin) / CLOCKS_PER_SEC;
#endif

    puts(maze);

#ifdef BENCH
    printf("generated (%dx%d) maze in %f seconds\n", height, width, elapsed_secs);
#endif

    free(maze);

    return 0;
}
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

#include "include/maze.h"
#include "include/heap.h"
#include "include/random.h"

typedef struct Pair {
    snumber x;
    snumber y;
} Pair;

int main() {
    Maze* maze = newMaze(100, 50);
    Heap* heap = newHeap();
    init_random();

    snumber fitness = solve(maze, heap);
    snumber best_fitness = fitness;
    printMaze(maze);
    printf("Fitness: %d\n", fitness);

    printMaze(maze);
    const snumber make_mutations = 10;

    clock_t begin = clock();
    long unsigned int loops = 0;

    while (best_fitness < 100000) {
        loops++;
        Pair mutations[make_mutations];
        snumber made_mutations = (get_next(make_mutations - 1)) + 1;
        for (int i = 0; i < made_mutations; ++i) {
            mutations[i].x = (get_next(maze->width - 3)) + 1;
            mutations[i].y = (get_next(maze->height - 2)) + 1;
            setContent(maze, mutations[i].x, mutations[i].y, 1 - getContent(maze, mutations[i].x, mutations[i].y));
        }

        fitness = solve(maze, heap);

        if (fitness > best_fitness) {
            if (fitness >= 4500) { // && fitness % 10 == 0) {
                printf("\e[1;1H\e[2J");
                printMaze(maze);
                printf("Fitness: %d\n", fitness);
                clock_t end = clock();
                double elapsed_secs = (double) (end - begin) / CLOCKS_PER_SEC;
                printf("Took %f seconds to reach %d fitness\nCalculating at %f muations/s\n", elapsed_secs, fitness, loops / elapsed_secs);
                usleep(100000);
                //exit(0);
            }
            best_fitness = fitness;
            resetMaze(maze);
        } else {
            resetMaze(maze);
            for (int i = 0; i < made_mutations; ++i) {
                setContent(maze, mutations[i].x, mutations[i].y, 1 - getContent(maze, mutations[i].x, mutations[i].y));
            }
        }
    }

    freeHeap(&heap);
    freeMaze(&maze);


    return 0;
}
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "src/maze.c"
#include "include/maze.h"
#include "include/heap.h"

/*char** mazeAlloc() {
    char** maze = malloc(sizeof(char*) * HEIGHT);

    for (int i = 0; i < HEIGHT; i++) {
        maze[i] = malloc((sizeof(char) * WIDTH) + 1);
    }

    return maze;
}

char** mazeCalloc() {
    char** maze = malloc(sizeof(char*) * HEIGHT);
    for (int i = 0; i < HEIGHT; i++) {
        maze[i] = malloc((sizeof(char) * WIDTH) + 1);
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

void printFancyMaze(char** maze) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; ++j) {
            switch (maze[i][j]) {
                case '#':
                    printf(WALL);
                    break;
                case '.':
                    printf(EMPTY);
                    break;
                case 'm':
                    printf(PATH);
                    break;
                case 'o':
                    printf(EXPLORED);
                    break;
            }
        }
        printf("\n");
    }
}

void freeMaze(char** maze) {
    for (int i = 0; i < HEIGHT; i++) {
        free(maze[i]);
    }
    free(*maze);
}

void mutate(char** maze) {
    for (uint i = 0; i < rand() % 5 + 1; ++i) {  // between 1 and 5 mutations
        uint h = rand() % (HEIGHT-2) + 1;
        uint w = rand() % (WIDTH-2) + 1;
        bool flip = rand() % 100 + 1 >= 50;

        if (flip) {
            maze[h][w] = '#';
        } else {
            maze[h][w] = '.';
        }

        maze[1][1] = '.';
        maze[HEIGHT-2][WIDTH-2] = '.';
    }
}*/

typedef struct Pair {
    snumber x;
    snumber y;
} Pair;

int main() {
    Maze* maze = newMaze(60, 20);
    Heap* heap = newHeap();

    snumber fitness = solve(maze, heap);
    snumber best_fitness = fitness;
    printMaze(maze);
    printf("Fitness: %d\n", fitness);

    printMaze(maze);
    const snumber make_mutations = 5;

    clock_t begin = clock();

    while (best_fitness < 1000) {
        Pair mutations[make_mutations];
        snumber made_mutations = (rand() % (make_mutations - 1)) + 1;
        for (int i = 0; i < made_mutations; ++i) {
            mutations[i].x = (rand() % (maze->width - 3)) + 1;
            mutations[i].y = (rand() % (maze->height - 2)) + 1;
            setContent(maze, mutations[i].x, mutations[i].y, 1 - getContent(maze, mutations[i].x, mutations[i].y));
        }

        fitness = solve(maze, heap);

        if (fitness > best_fitness) {
            if (fitness >= 840) {
                printf("\e[1;1H\e[2J");
                printMaze(maze);
                printf("Fitness: %d\n", fitness);
                clock_t end = clock();
                double elapsed_secs = (double) (end - begin) / CLOCKS_PER_SEC;
                printf("Took %f seconds to reach %d fitness", elapsed_secs, fitness);
                usleep(100000);
                exit(0);
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

    /*
    char** best = mazeCalloc();
    char** mutated = mazeAlloc();
    char** solved = mazeAlloc();
    uint best_fitness = 0;

    printMaze(best);

    while (best_fitness <= 100) {
        mazeCopy(best, mutated);
        mutate(mutated);

        mazeCopy(mutated, solved);
        printMaze(mutated);

        //Solver sol = Solver(solved);
        //uint fitness = sol.solve();
        int fitness = 0;

        if (best_fitness < fitness) {
            mazeCopy(mutated, best);
            best_fitness = fitness;
            printMaze(solved);
        }
    }

    printFancyMaze(solved);

    freeMaze(best);
    freeMaze(mutated);
    freeMaze(solved);
*/
    return 0;
}
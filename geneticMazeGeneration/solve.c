#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "include/maze.h"
#include "include/heap.h"

int main(int argc, char *argv[]) {
    // size input is calculated + 1 because the maze generator does not count a the outer walls (right and below) to size
    int width = strtoul(argv[2], NULL, 10) + 1;
    int height = strtoul(argv[1], NULL, 10) + 1;
    Maze* maze = newMaze(width, height);
    Heap* heap = newHeap();

    for (int x = 0; x < maze->height; ++x) {
        for (int y = 0; y < maze->width - 1; ++y) {
            char c = getchar();
            //putchar(c);
            switch (c) {
                case '#':
                    setContent(maze, y, x, WALL);
                    break;
                case '.':
                    setContent(maze, y, x, EMPTY);
            }
        }
        getchar(); // get \n
        //printf("\n");
    }
    //printMaze(maze);
    //return 0;

    //printMaze(maze);
    printf("read");

    clock_t begin = clock();
    solve(maze, heap);
    clock_t end = clock();
    double elapsed_secs = (double) (end - begin) / CLOCKS_PER_SEC;

    //printMaze(maze);
    printf("Took %f seconds to solve maze (height=%d, width=%d)", elapsed_secs, height, width);

    freeHeap(&heap);
    freeMaze(&maze);

    return 0;
}

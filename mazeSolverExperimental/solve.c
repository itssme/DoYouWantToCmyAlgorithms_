#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "include/maze.h"


int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: ./solver <height> <width> < maze.txt");
        return 1;
    }

    // size input is calculated + 1 because the maze generator does not count the outer walls (right and below) to size
    int width = atoi(argv[2]) + 1;
    int height = atoi(argv[1]) + 1;

    Maze* maze = newMaze(width, height);

    int i = 0;
    for (int x = 0; x < maze->height; ++x) {
        for (int y = 0; y < maze->width - 1; ++y) {
            char c = getchar();
            //putchar(c);
            switch (c) {
                case '#':
                    setContent(maze, i, WALL);
                    break;
                case '.':
                    setContent(maze, i, EMPTY);
            }
            i++;
        }
        getchar(); // get \n
        i++;
        //printf("\n");
    }
    //printMaze(maze);
    //return 0;

#ifdef VISUALIZE
    wrefresh(window);
    usleep(2000000);
#endif

    Queue* queue = newQueue();

    clock_t begin = clock();
    solve(maze, queue);
    clock_t end = clock();
    double elapsed_secs = (double) (end - begin) / CLOCKS_PER_SEC;

    freeQueue(&queue);

#ifdef VISUALIZE
    usleep(2000000);
#else
    printMaze(maze);
#endif

    printf("Took %f seconds to solve maze (height=%d, width=%d)", elapsed_secs, height, width);

    freeMaze(&maze);

    return 0;
}

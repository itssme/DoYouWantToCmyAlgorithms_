#include <string.h>
#include <math.h>

#include "maze.h"

typedef enum FieldState {
    EMPTY = 0,
    WALL = 1,
    NEWLINE = 2,
    PATH = 3,
    EXPLORED = 4
} FieldState;

Maze* newMaze(snumber width, snumber height) {
    width++;
    snumber length = width * height;

    Maze* maze = malloc(sizeof(Maze) + length);
    maze->width = width;
    maze->height = height;
    maze->data = (char*) (maze + 1);
    memset(maze->data, EMPTY, length);

    for (snumber i = width - 1; i < length; i += width) {
        maze->data[i - (width - 1)] = WALL;
        maze->data[i - 1] = WALL;
        maze->data[i] = NEWLINE;
    }

    memset(maze->data + 1, WALL, width - 3);
    memset(maze->data + 1 + (length - width), WALL, width - 3);

    return maze;
}

void freeMaze(Maze** maze) {
    if (maze != NULL) {
        free(*maze);
        *maze = NULL;
    }
}

void printMaze(Maze* maze) {
    static string map[5] = {
            "\033[0m ",   // empty
            "\33[41m ",   // wall
            "\033[0m \n", // newline
            "\33[42m ",   // path
            "\33[44m "    // explored
    };

    snumber length = maze->width * maze->height;

    for (snumber i = 0; i < length; ++i) {
        fputs(map[maze->data[i]], stdout);
    }
}

char getContent(Maze* maze, snumber x, snumber y) {
    return maze->data[y * maze->width + x];
}

static void setContent(Maze* maze, snumber x, snumber y, FieldState state) {
    maze->data[y * maze->width + x] = state;
}


static void insertNext(Maze* maze, Heap* heap, const Point p, snumber x, snumber y) {
    x += p.x;
    y += p.y;
    if (getContent(maze, x, y) != EMPTY) {
        return;
    }
    Point nP;
    nP.x = x;
    nP.y = y;

    snumber x_diff = x - (maze->width - 3);
    snumber y_diff = y - (maze->height - 2);

    nP.baseCost = p.baseCost + 1;
    //nP.heuCost = nP.baseCost + sqrtf(x_diff * x_diff + y_diff * y_diff) * 1.01;//(abs(x_diff) + abs(y_diff)) * 1.01;
    nP.heuCost = (abs(x_diff) + abs(y_diff)) * 1.01;
    heapInsert(heap, &nP);
    setContent(maze, x, y, EXPLORED);
}

snumber solve(Maze* maze, Heap* heap) {
    clearHeap(heap);

    Point p = {1,1,0,0};

    heapInsert(heap, &p);
    setContent(maze, p.x, p.y, EXPLORED);
    snumber loops = 0;

    #ifdef INFO
    float* cost = malloc(maze->width * maze->height * sizeof(float));

    for (int i = 0; i < (maze->width * maze->height); ++i) {
        cost[i] = 0;
    }
    #endif

    while (heapExtract(heap, &p)) {
        if (p.x == maze->width - 3 && p.y == maze->height - 2) {
            #ifdef INFO
            free(cost);
            #endif
            return loops;
        }

        #ifdef INFO
        printMaze(maze);
        #endif

        //setContent(maze, p.x, p.y, PATH);
        //printMaze(maze);
        //printf("x= %d y=%d\n", p.x, p.y);

        insertNext(maze, heap, p, 0, 1);
        insertNext(maze, heap, p, 0, -1);
        insertNext(maze, heap, p, 1, 0);
        insertNext(maze, heap, p, -1, 0);

        #ifdef INFO
        for (int i = 0; i < heap->size; ++i) {
            cost[heap->data[i].x + heap->data[i].y * maze->width] = heap->data[i].heuCost;
        }

        for (int i = 0; i < maze->height; ++i) {
            for (int j = 0; j < maze->width; ++j) {
                printf("%5.1f ", cost[i*maze->width + j]);
            }
            putchar('\n');
        }
        getchar();
        #endif

        //insertNext(maze, heap, p, -1, -1);
        //insertNext(maze, heap, p, 1, 1);
        //insertNext(maze, heap, p, -1, 1);
        //insertNext(maze, heap, p, 1, -1);

        loops++;
    }
    #ifdef INFO
    free(cost);
    #endif
    return 0;
}

void resetMaze(Maze* maze) {
    for (int i = 0; i < maze->height; ++i) {
        for (int j = 0; j < maze->width-1; ++j) {
            maze->data[i*maze->width + j] = maze->data[i*maze->width + j] == WALL;
        }
    }
}

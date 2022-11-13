#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "maze.h"

#ifdef VISUALIZE
WINDOW* window = NULL;
bool setup = NULL;
#endif

Maze* newMaze(snumber width, snumber height) {
    width++;
    snumber length = width * height;
    printf("Allocating %luMiB of memory for maze\n",
           (sizeof(Maze) + length + sizeof(BackPoint) * length) / 1049000);

    Maze* maze = malloc(sizeof(Maze) + length + sizeof(BackPoint) * length);
    maze->width = width;
    maze->height = height;
    maze->data = (((char*) (maze + 1)) + (sizeof(BackPoint) * length));
    memset(maze->data, EMPTY, length);
    maze->backIdx = 0;
    maze->back = (BackPoint*) (maze + 1);

    for (snumber i = width - 1; i < length; i += width) {
        maze->data[i - (width - 1)] = WALL;
        maze->data[i - 1] = WALL;
        maze->data[i] = NEWLINE;
    }

    memset(maze->data + 1, WALL, width - 3);
    memset(maze->data + 1 + (length - width), WALL, width - 3);

#ifdef VISUALIZE
    initscr();
    cbreak();
    curs_set(0);
    noecho();
    setup = TRUE;

    resizeterm(height, width);

    window = newwin(height, width, 0, 0);
    start_color();

    init_pair(EMPTY, COLOR_BLACK, COLOR_BLACK);
    init_pair(WALL, COLOR_RED, COLOR_RED);
    init_pair(NEWLINE, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(PATH, COLOR_GREEN, COLOR_GREEN);
    init_pair(EXPLORED, COLOR_BLUE, COLOR_BLUE);
    init_pair(EXPLORING, COLOR_CYAN, COLOR_CYAN);
#endif

    return maze;
}

void freeMaze(Maze** maze) {
#ifdef VISUALIZE
    endwin();
#endif
    if (maze != NULL) {
        free(*maze);
        *maze = NULL;
    }
}

void printMaze(Maze* maze) {
    static string map[6] = {
            "\033[0m ",   // empty
            "\33[41m ",   // wall
            "\033[0m \n", // newline
            "\33[42m ",   // path
            "\33[44m ",   // explored
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

#ifdef VISUALIZE
void setContentCurses(snumber x, snumber y, enum FieldState state) {
    wattron(window, COLOR_PAIR(state));
    mvwaddch(window, y, x, ' ');
    wattroff(window, COLOR_PAIR(state));
    if (setup == FALSE) {
        wrefresh(window);
        usleep(10000);
    }
}
#endif

void setContent(Maze* maze, snumber x, snumber y, FieldState state) {
#ifdef VISUALIZE
    setContentCurses(x, y, state);
#endif
    maze->data[y * maze->width + x] = state;
}

static void insertBack(Maze* maze, const Point* p, Point* nP, snumber x, snumber y) {
    maze->backIdx++;
    maze->back[maze->backIdx].x = nP->x;
    maze->back[maze->backIdx].y = nP->y;
    maze->back[maze->backIdx].predIndex = p->backPointIdx;
    maze->back[maze->backIdx].baseCost = maze->back[p->backPointIdx].baseCost + 1;

    snumber x_diff = x - (maze->width - 3);
    snumber y_diff = y - (maze->height - 2);
    //nP->heuCost = nP.baseCost + sqrtf(x_diff * x_diff + y_diff * y_diff) * 1.01;//(abs(x_diff) + abs(y_diff)) * 1.01;
    //nP->heuCost = maze->back[maze->backIdx].baseCost + (abs(x_diff) + abs(y_diff)) * 1.01;  // A* (with Manhattan distance)
    nP->heuCost = maze->back[maze->backIdx].baseCost; // Dijkstra;
    //nP->heuCost = (abs(x_diff) + abs(y_diff)) * 1.01; // Best-first-search
    nP->backPointIdx = maze->backIdx;
}

static void insertNext(Maze* maze, Heap* heap, const Point* p, snumber x, snumber y) {
    x += p->x;
    y += p->y;
    if (getContent(maze, x, y) != EMPTY) {
        return;
    }
    Point nP;
    nP.x = x;
    nP.y = y;

    insertBack(maze, p, &nP, x, y);
    heapInsert(heap, &nP);
#ifdef VISUALIZE
    setContent(maze, x, y, EXPLORING);
#else
    setContent(maze, x, y, EXPLORED);
#endif
}

snumber solve(Maze* maze, Heap* heap) {
    clearHeap(heap);

#ifdef VISUALIZE
    setup = FALSE;
#endif

    Point p = {1, 1, 0, 0}; //0};
    maze->back[0].baseCost = 0;
    maze->back[0].predIndex = 0;

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

            snumber backI = p.backPointIdx;
            snumber len = 0;
            while (backI != 0) {
                setContent(maze, maze->back[backI].x, maze->back[backI].y, PATH);
                backI = maze->back[backI].predIndex;
                len++;
            }
            setContent(maze, 1, 1, PATH);

            return loops;
        }

#ifdef VISUALIZE
        setContentCurses(p.x, p.y, EXPLORED);
#endif

#ifdef INFO
        printMaze(maze);
#endif

        insertNext(maze, heap, &p, 0, 1);
        insertNext(maze, heap, &p, 0, -1);
        insertNext(maze, heap, &p, 1, 0);
        insertNext(maze, heap, &p, -1, 0);

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

        // Diagonal Moves
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
        for (int j = 0; j < maze->width - 1; ++j) {
            // WARNING
            // Narrowing conversion from 'int' to signed type 'char' is implementation-defined
            maze->data[i * maze->width + j] = maze->data[i * maze->width + j] == WALL;
        }
    }
    maze->backIdx = 0;
}

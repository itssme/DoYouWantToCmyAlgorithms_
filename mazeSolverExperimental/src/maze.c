#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "maze.h"

typedef const char* string;

Maze* newMaze(int width, int height) {
    width++;
    int length = width * height;
    printf("Allocating %luMiB of memory for maze\n",
           (sizeof(Maze) + length) / 1049000);

    Maze* maze = malloc(sizeof(Maze) + length);
    maze->width = width;
    maze->height = height;
    maze->data = (((char*) (maze + 1)));
    memset(maze->data, EMPTY, length);

    for (int i = width - 1; i < length; i += width) {
        maze->data[i] = NEWLINE;
    }

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

    int length = maze->width * maze->height;

    for (int i = 0; i < length; ++i) {
        fputs(map[(int) maze->data[i]], stdout);
    }
}

char getContent(Maze* maze, int index) {
    return maze->data[index];
}

#ifdef VISUALIZE
void setContentCurses(Maze* maze, int index, enum FieldState state) {
    wattron(window, COLOR_PAIR(state));
    int x = index % maze->width;
    int y = index / maze->width;
    mvwaddch(window, y, x, ' ');
    wattroff(window, COLOR_PAIR(state));
    if (setup == FALSE) {
        wrefresh(window);
        usleep(10000);
    }
}
#endif

void setContent(Maze* maze, int index, FieldState state) {
#ifdef VISUALIZE
    setContentCurses(maze, index, state);
#endif
    maze->data[index] = state;
}

static void insertNext(Maze* maze, Queue* queue, int index, int read_index) {
    if (getContent(maze, index) != EMPTY) {
        return;
    }
    Point p = {read_index, index};
    queueInsert(queue, &p);
#ifdef VISUALIZE
    setContent(maze, index, EXPLORING);
#else
    setContent(maze, index, EXPLORED);
#endif
}

int solve(Maze* maze, Queue* queue) {

#ifdef VISUALIZE
    setup = FALSE;
#endif

    Point p = {0, maze->width + 1};
    queueInsert(queue, &p);
    setContent(maze, p.index, EXPLORED);

    int end_index = maze->width * (maze->height - 2) + (maze->width - 3);
    int read_index;
    while (queueRead(queue, &p, &read_index)) {
        if (p.index == end_index) {
            while (read_index != 0) {
                setContent(maze, queue->data[read_index].index, PATH);
                read_index = queue->data[read_index].previous;
            }
            setContent(maze, maze->width + 1, PATH);
            break;
        }

#ifdef VISUALIZE
        setContentCurses(maze, p.index, EXPLORED);
#endif

        insertNext(maze, queue, p.index + 1, read_index);
        insertNext(maze, queue, p.index - 1, read_index);
        insertNext(maze, queue, p.index + maze->width, read_index);
        insertNext(maze, queue, p.index - maze->width, read_index);
    }
    return 0;
}
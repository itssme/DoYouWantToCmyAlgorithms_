#include <stdio.h>
#include <stdlib.h>
#include <zconf.h>

#include "maze_generator_recursive_backtracking.h"
#include "types.h"

const uint pos_change[4][2] = {
        {0, -1},
        {0, 1},
        {1, 0},
        {-1, 0}
};

struct node {
    struct node* pred_node;
    uint y;
    uint x;
};

node* get_next(node* maze, node* node, uint height, uint width) {
    int i = rand() & 3;

    for (uint attempt = 0; attempt < 4; ++attempt) {
        uint x = node->x + pos_change[i][0];
        uint y = node->y + pos_change[i][1];

        i = (i + 1) & 3;

        uint idx = x * width + y;

        if (y < width && x < height && maze[idx].pred_node == NULL && ! (x == 0 && y == 0)) {
            maze[idx].pred_node = node;
            return & (maze[idx]);
        }
    }
    return NULL;
}

void print_maze(char** maze, uint size_h) {
    for (uint i = 0; i < size_h; ++i) {
        puts(maze[i]);
    }
}

char** generate_maze(uint height, uint width) {
    if (height & 1 || width & 1) {
        printf("Maze height and width must be even numbers\n");
        return NULL;
    }

    // x y y y y . . width
    // x
    // x
    // x
    // .
    // .
    // height

    // allocate two dimensional array of size (height / 2) * (width / 2) of pointers to nodes
    //struct node* pre_maze = (struct node*) calloc(height * width / 4, sizeof(struct node));
    struct node* pre_maze = (struct node*) malloc(height * width / 4 * sizeof(struct node));
    for (uint i = 0; i < height * width / 4; ++i) {
        pre_maze[i].pred_node = NULL;
        pre_maze[i].x = i / (width / 2);
        pre_maze[i].y = i % (width / 2);
    }

    // allocate two dimensional char array of size height * width
    char** maze = (char**) malloc((height + 1) * sizeof(char*));
    for (uint i = 0; i < height + 1; ++i) {
        maze[i] = (char*) malloc(width + 1);
        for (uint j = 0; j < width + 1; ++j) {
            maze[i][j] = '#';
        }
    }

    node* current_node = get_next(pre_maze, pre_maze, height / 2, width / 2);

    while (current_node->x || current_node->y) {
        node* next_node = get_next(pre_maze, current_node, height / 2, width / 2);

        if (next_node == NULL) {
            maze[current_node->x * 2 + 1][current_node->y * 2 + 1] = ' ';
            if (current_node->x > current_node->pred_node->x) {
                maze[current_node->x * 2][current_node->y * 2 + 1] = ' ';
            } else if (current_node->x < current_node->pred_node->x) {
                maze[current_node->x * 2 + 2][current_node->y * 2 + 1] = ' ';
            } else if (current_node->y < current_node->pred_node->y) {
                maze[current_node->x * 2 + 1][current_node->y * 2 + 2] = ' ';
            } else if (current_node->y > current_node->pred_node->y) {
                maze[current_node->x * 2 + 1][current_node->y * 2] = ' ';
            }

            current_node = current_node->pred_node;
            maze[current_node->x * 2 + 1][current_node->y * 2 + 1] = ' ';
        } else {
            current_node = next_node;
        }
    }

    maze[1][1] = 'S';
    maze[height - 1][width - 1] = 'E';

    print_maze(maze, height + 1);

    free(pre_maze);

    // free memory used by maze
    //for (uint i = 0; i < height + 1; i++ ) {
    //    free(maze[i]);
    //}
    //free(maze);

    return maze;
}
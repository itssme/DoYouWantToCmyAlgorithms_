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

node* get_next(node*** maze, node* node, uint height, uint width) {
    int i = rand() % 4;

    i = i % 4;

    uint attempt = 0;
    while (attempt != 4) {
        attempt += 1;
        uint x = pos_change[i][0];
        uint y = pos_change[i][1];
        x = node->x + x;
        y = node->y + y;

        i = (i + 1) % 4;

        if (x < 0 || y < 0 || y >= height || x >= width) {continue;}

        if (maze[x][y] == NULL) {
            struct node* new_node = malloc(sizeof(node));
            new_node->y = y;
            new_node->x = x;
            new_node->pred_node = node;
            maze[x][y] = new_node;
            return new_node;
        }
    }
    return NULL;
}

void print_maze(char** maze, uint size_h) {
    for (uint i = 0; i < size_h; ++i) {
        printf("%s\n", maze[i]);
    }
}

char** generate_maze(uint height, uint width) {
    if (height & 1 || width & 1) {
        printf("Maze height and width must be even numbers\n");
        return NULL;
    }

    // allocate two dimensional array of size (height / 2) * (width / 2) of pointers to nodes
    struct node*** pre_maze = (struct node***) calloc(height / 2, sizeof(struct node**));
    for (uint i = 0; i < height / 2; i++) {
        pre_maze[i] = (struct node**) calloc(width / 2, sizeof(struct node*));
    }

    // allocate two dimensional char array of size height * width
    char** maze = (char**) calloc(height + 1, sizeof(char*));
    for (uint i = 0; i < height + 1; i++) {
        maze[i] = (char*) calloc(width + 1, sizeof(char));
    }

    for (uint i = 0; i < height + 1; ++i) {
        for (uint j = 0; j < height + 1; ++j) {
            maze[i][j] = '#';
        }
    }

    node* start_node = malloc(sizeof(node));
    start_node->y = start_node->x = 0;
    pre_maze[0][0] = start_node;
    node* current_node = get_next(pre_maze, start_node, height / 2, width / 2);

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

    //print_maze(maze, height + 1);

    // free memory used by pre maze
    for (uint i = 0; i < height / 2; i++ ) {
        for (uint j = 0; j < width / 2; j++ ) {
            free(pre_maze[i][j]);
        }
        free(pre_maze[i]);
    }
    free(pre_maze);

    // free memory used by maze
    //for (uint i = 0; i < height; i++ ) {
    //    free(maze[i]);
    //}
    //free(maze);

    return maze;
}
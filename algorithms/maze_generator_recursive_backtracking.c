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
#ifdef BIG_MAZE
    u64 pred_node;
#else
    u32 pred_node;
#endif
    u32 y;
    u32 x;
};

#ifdef BIG_MAZE
inline const u64 get_next(node* maze, u64 node_idx, u32 height, u32 width) {
    int i = rand() & 3;

    for (uint attempt = 0; attempt < 4; ++attempt) {
        u32 x = maze[node_idx].x + pos_change[i][0];
        u32 y = maze[node_idx].y + pos_change[i][1];

        i = (i + 1) & 3;

        u64 idx = x * width + y;

        if (y < width && x < height && maze[idx].pred_node == -2) {
            maze[idx].pred_node = node_idx;
            return idx;
        }
    }
    return (u64) -1;
}
#else
inline const u32 get_next(node* maze, u32 node_idx, u32 height, u32 width) {
    int i = rand() & 3;

    for (uint attempt = 0; attempt < 4; ++attempt) {
        u32 x = maze[node_idx].x + pos_change[i][0];
        u32 y = maze[node_idx].y + pos_change[i][1];

        i = (i + 1) & 3;

        u32 idx = x * width + y;

        if (y < width && x < height && maze[idx].pred_node == -2) {
            maze[idx].pred_node = node_idx;
            return idx;
        }
    }
    return (u32) -1;
}
#endif

char* generate_maze(u32 height, u32 width) {
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

    struct node* pre_maze = (struct node*) malloc(height * width / 4 * sizeof(struct node));
    for (u64 i = 0; i < height * width / 4; ++i) {
        pre_maze[i].pred_node = -2;
        pre_maze[i].x = i / (width / 2);
        pre_maze[i].y = i % (width / 2);
    }

    u64 length = (width + 2) * (height + 1);

    char* maze = (char*) malloc((length));
    for (u64 i = 0; i < length; ++i) {
        maze[i] = '#';
    }

    for (u64 i = width + 1; i < length; i += width + 2) {
        maze[i] = '\n';
    }

    _Static_assert((((u32) -2) < ((u32) -1)), "can't to unsigned int magic on your system :(");
    _Static_assert((((u64) -2) < ((u64) -1)), "can't to unsigned int magic on your system :(");

    maze[length - 1] = '\0';

    #ifdef BIG_MAZE
    u64 current_node = get_next(pre_maze, 0, height / 2, width / 2);
    u64 next_node = 0;
    u64 null_node = (u64) -1;
    pre_maze[0].pred_node = null_node;
    #else
    u32 current_node = get_next(pre_maze, 0, height / 2, width / 2);
    u32 next_node = 0;
    u32 null_node = (u32) -1;
    pre_maze[0].pred_node = null_node;
    #endif

    while (pre_maze[current_node].pred_node != null_node) {
         next_node= get_next(pre_maze, current_node, height / 2, width / 2);

        if (next_node == null_node) {
            u32 x = pre_maze[current_node].x;
            u32 y = pre_maze[current_node].y;

            uint off_x = (x <= pre_maze[pre_maze[current_node].pred_node].x) + (x < pre_maze[pre_maze[current_node].pred_node].x);
            uint off_y = (y <= pre_maze[pre_maze[current_node].pred_node].y) + (y < pre_maze[pre_maze[current_node].pred_node].y);

            maze[(x * 2 + off_x) * (width + 2) + y * 2 + off_y] = ' ';
            maze[(x * 2 + 1) * (width + 2) + y * 2 + 1] = ' ';

            current_node = pre_maze[current_node].pred_node;
        } else {
            current_node = next_node;
        }
    }

    maze[width + 3] = 'S';
    maze[height * (width + 2) - 3] = 'E';

    puts(maze);

    free(pre_maze);

    // free memory used by maze
    //for (uint i = 0; i < height + 1; i++ ) {
    //    free(maze[i]);
    //}
    //free(maze);

    return maze;
}
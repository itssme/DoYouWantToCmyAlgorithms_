#ifndef DOYOUWANTTOCMYALGORITHMS__MAZE_GENERATOR_RECURSIVE_BACKTRACKING_H
#define DOYOUWANTTOCMYALGORITHMS__MAZE_GENERATOR_RECURSIVE_BACKTRACKING_H

#include <stdio.h>
#include <stdlib.h>
#include <zconf.h>

#include "maze_generator_recursive_backtracking.h"
#include "types.h"

const uint pos_change[4][2];
struct node;
typedef struct node node;
const u32 get_next(node* maze, u32 node, u32 height, u32 width);
char* generate_maze(u32 height, u32 width);

#endif //DOYOUWANTTOCMYALGORITHMS__MAZE_GENERATOR_RECURSIVE_BACKTRACKING_H

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
node* get_next(node* maze, node* node, uint height, uint width);
void print_maze(char** maze, uint size_h);
char** generate_maze(uint height, uint width);

#endif //DOYOUWANTTOCMYALGORITHMS__MAZE_GENERATOR_RECURSIVE_BACKTRACKING_H

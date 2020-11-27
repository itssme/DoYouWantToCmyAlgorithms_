#include <iostream>
#include <cstring>
#include "src/astar.cpp"

#define WALL "\33[41m \033[0m"
#define EMPTY " "
#define PATH "\33[42m \033[0m"
#define EXPLORED "\33[44m \033[0m"

char** mazeAlloc() {
    char** maze = (char**) malloc(sizeof(char*) * HEIGHT);

    for (int i = 0; i < HEIGHT; i++) {
        maze[i] = (char*) malloc((sizeof(char) * WIDTH) + 1);
    }

    return maze;
}

char** mazeCalloc() {
    char** maze = (char**) malloc(sizeof(char*) * HEIGHT);
    for (int i = 0; i < HEIGHT; i++) {
        maze[i] = (char*) malloc((sizeof(char) * WIDTH) + 1);
        maze[i][0] = '#';
        for (int j = 1; j < WIDTH - 1; j++) {
            maze[i][j] = '.';
        }
        maze[i][WIDTH] = '\0';
    }

    for (int i = 0; i < HEIGHT; i++) {
        maze[i][0] = '#';
        maze[i][WIDTH - 1] = '#';
    }

    for (int i = 0; i < WIDTH - 1; i++) {
        maze[0][i] = '#';
        maze[HEIGHT - 1][i] = '#';
    }

    return maze;
}

void mazeCopy(char** src, char** dest) {
    for (int i = 0; i < HEIGHT; ++i) {
        memcpy(dest[i], src[i], (sizeof(char) * WIDTH) + 1);
    }
}

void printMaze(char** maze) {
    for (int i = 0; i < HEIGHT; i++) {
        puts(maze[i]);
    }
}

void printFancyMaze(char** maze) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; ++j) {
            switch (maze[i][j]) {
                case '#':
                    printf(WALL);
                    break;
                case '.':
                    printf(EMPTY);
                    break;
                case 'm':
                    printf(PATH);
                    break;
                case 'o':
                    printf(EXPLORED);
                    break;
            }
        }
        printf("\n");
    }
}

void free(char** maze) {
    for (int i = 0; i < HEIGHT; i++) {
        free(maze[i]);
    }
    free(*maze);
}

void mutate(char** maze) {
    for (uint i = 0; i < rand() % 5 + 1; ++i) {  // between 1 and 5 mutations
        uint h = rand() % (HEIGHT-2) + 1;
        uint w = rand() % (WIDTH-2) + 1;
        bool flip = rand() % 100 + 1 >= 50;

        if (flip) {
            maze[h][w] = '#';
        } else {
            maze[h][w] = '.';
        }

        maze[1][1] = '.';
        maze[HEIGHT-2][WIDTH-2] = '.';
    }
}



int main() {
    char** best = mazeCalloc();
    char** mutated = mazeAlloc();
    char** solved = mazeAlloc();
    uint best_fitness = 0;

    printMaze(best);

    while (best_fitness <= 100) {
        mazeCopy(best, mutated);
        mutate(mutated);

        mazeCopy(mutated, solved);
        printMaze(mutated);

        Solver sol = Solver(solved);
        uint fitness = sol.solve();

        if (best_fitness < fitness) {
            mazeCopy(mutated, best);
            best_fitness = fitness;
            printMaze(solved);
        }
        std::cout << fitness << std::endl;
    }

    printFancyMaze(solved);

    free(best);
    free(mutated);
    free(solved);

    return 0;
}

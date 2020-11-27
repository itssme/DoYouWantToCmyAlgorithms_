#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#define WIDTH 20
#define HEIGHT 20

typedef unsigned int uint;


struct Point {

    Point(uint x, uint y) : x(x), y(y),
                            distance(sqrtf(((HEIGHT - 2) - x) * ((HEIGHT - 2) - x) +
                                           ((WIDTH - 2) - y) * ((WIDTH - 2) - y))) {
    }

    uint x;
    uint y;
    float distance;

    bool operator<(const Point &other) {
        return distance >= other.distance;
    }
};

class Solver {
public:
    char** maze;

    inline void mark(uint x, uint y) const {
        maze[x][y] = 'm';
    }

    bool isFree(uint x, uint y) {
        return maze[x][y] == '.';
    }

    uint removeWrongPaths(uint x, uint y) {
        maze[x][y] = 'o';
        if ((x == HEIGHT - 2 && y == WIDTH - 2)) {
            return 1;
        }
        uint result = 0;
        if (maze[x - 1][y] == 'm') {
            result += removeWrongPaths(x - 1, y);
        }
        if (maze[x + 1][y] == 'm') {
            result += removeWrongPaths(x + 1, y);
        }
        if (maze[x][y - 1] == 'm') {
            result += removeWrongPaths(x, y - 1);
        }
        if (maze[x][y + 1] == 'm') {
            result += removeWrongPaths(x, y + 1);
        }
        if (!result) {
            maze[x][y] = '.';
        }
        return result;
    }

    void pushIf(std::vector<Point> &queue, uint x, uint y) {
        if (isFree(x, y)) {
            queue.push_back({x, y});
            std::push_heap(queue.begin(), queue.end());
        }
    }

    int solve() {
        /*uint maxIndex = WIDTH * HEIGHT;
        uint index = 0;
        while (index < maxIndex) {
            int c = std::cin.get();
            if (c == '#') {
                set(index++, '#');
            } else if (c == '.') {
                set(index++, '.');
            }
        }*/

        std::vector<Point> queue;
        queue.push_back({1, 1});
        std::push_heap(queue.begin(), queue.end());

        uint loop = 0;
        while (!queue.empty()) {
            loop++;
            Point p = queue.front();
            std::pop_heap(queue.begin(), queue.end());
            queue.pop_back();

            mark(p.x, p.y);
            if (p.x == HEIGHT - 2 && p.y == WIDTH - 2) {
                break;
            }

            pushIf(queue, p.x - 1, p.y);
            pushIf(queue, p.x + 1, p.y);
            pushIf(queue, p.x, p.y - 1);
            pushIf(queue, p.x, p.y + 1);
        }

        removeWrongPaths(1, 1);

        for (uint x = 1; x < HEIGHT - 1; x++) {
            for (uint y = 1; y < WIDTH - 1; y++) {
                if (maze[x][y] == 'o' && (maze[x - 1][y] == 'o' || maze[x + 1][y] == 'o') &&
                    (maze[x][y - 1] == 'o' || maze[x][y + 1] == 'o')) {
                    maze[x][y] = '.';
                }
            }
        }

        return loop;
    }

    Solver(char** maze) : maze(maze) {}
};

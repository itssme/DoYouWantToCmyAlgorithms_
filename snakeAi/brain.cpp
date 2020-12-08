#include <unistd.h>
#include "game.h"

int main() {
    VisualizedGame game;

    Move move = LEFT;
    while (game.tick(move)) {
        usleep(100000);

        int c = 0;
        int c_tmp = wgetch(game.window);
        while (c_tmp != ERR) {
            c = c_tmp;
            c_tmp = wgetch(game.window);
        }

        switch (c) {
            case 65:
                move = UP;
                break;
            case 66:
                move = DOWN;
                break;
            case 67:
                move = RIGHT;
                break;
            case 68:
                move = LEFT;
                break;
        }
    }

    return 0;
}

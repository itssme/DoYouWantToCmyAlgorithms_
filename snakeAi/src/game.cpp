#include <algorithm>
#include "game.h"

static bool cmp_pos(pos pos1, pos pos2) {
    return pos1.first == pos2.first && pos1.second == pos2.second;
}

Game::Game() {
    Game::new_food();
    this->snake.emplace_back(Game::max_x / 2, Game::max_y / 2);
    this->food.first += this->snake.front().first == this->food.first;
    this->food.second += this->snake.front().second == this->food.second;
}

void Game::new_food() {
    this->food.first = (rand() % Game::max_x - 1) + 1;
    this->food.second = (rand() % Game::max_y - 1) + 1;
}

bool Game::in_snake(const pos &pos1) const {
    return std::find_if(this->snake.begin(), this->snake.end(),
                        [pos1](const pos &p) {
                            return cmp_pos(pos1, p);
                        }) != this->snake.end();
}

bool Game::tick(Move move) {
    pos next_p = {0, 0};

    // 0 .. MAX_X
    // .
    // .
    // MAX_Y

    switch (move) {
        case LEFT:
            next_p.first = -1;
            break;
        case RIGHT:
            next_p.first = 1;
            break;
        case UP:
            next_p.second = -1;
            break;
        case DOWN:
            next_p.second = 1;
            break;
    }

    pos head = this->snake.front();
    next_p.first += head.first;
    next_p.second += head.second;
    if (next_p.first >= Game::max_x || next_p.second >= Game::max_y || next_p.first <= 0 || next_p.second <= 0
        || in_snake(next_p)) {
        return false;
    }

    add_head(next_p);

    if (cmp_pos(next_p, this->food)) {
        score++;

        do {
            new_food();
        } while (in_snake(this->food));
    } else {
        remove_back();
    }

    return true;
}

void Game::add_head(pos head) {
    this->snake.emplace_front(head);
}

void Game::remove_back() {
    this->snake.pop_back();
}

#include <game.h>

VisualizedGame::VisualizedGame() : Game() {
    initscr();
    cbreak();
    curs_set(0);
    noecho();
    timeout(0);

    resizeterm(Game::max_y + 2, Game::max_x + 2);

    window = newwin(Game::max_y + 1, Game::max_x + 1, 0, 0);
    wtimeout(window, 0);
    start_color();

    init_pair(EMPTY, COLOR_BLACK, COLOR_BLACK);
    init_pair(SNAKE, COLOR_RED, COLOR_RED);
    init_pair(FOOD, COLOR_GREEN, COLOR_GREEN);
    init_pair(WALL, COLOR_BLUE, COLOR_BLUE);

    this->food = {0,0};
    VisualizedGame::new_food();

    for (int i = 0; i < Game::max_y; ++i) {
        set_field({i, 0}, WALL);
        set_field({0, i}, WALL);
        set_field({Game::max_x, i}, WALL);
        set_field({i, Game::max_y}, WALL);
    }
    set_field({Game::max_x, Game::max_y}, WALL);

    wrefresh(window);
}

void VisualizedGame::set_field(pos pos1, Field field) {
    wattron(window, COLOR_PAIR(field));
    mvwaddch(window, pos1.second, pos1.first, ' ');
    wattroff(window, COLOR_PAIR(field));
}

void VisualizedGame::new_food() {
    set_field(this->food, SNAKE);
    Game::new_food();
    set_field(this->food, FOOD);
}

void VisualizedGame::add_head(pos head) {
    Game::add_head(head);
    set_field(head, SNAKE);
}

void VisualizedGame::remove_back() {
    set_field(this->snake.back(), EMPTY);
    Game::remove_back();
}

bool VisualizedGame::tick(Move move) {
    bool ret = Game::tick(move);
    wrefresh(this->window);
    return ret;
}

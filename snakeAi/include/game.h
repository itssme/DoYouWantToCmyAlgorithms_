#ifndef SNAKEAI_GAME_H
#define SNAKEAI_GAME_H

#include <deque>
#include <ncurses.h>

typedef std::pair<int, int> pos;

enum Move {
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Game {
private:
    bool in_snake(const pos &pos1) const;

public:
    static constexpr int max_x{25};
    static constexpr int max_y{25};
    int score;
    pos food;

    virtual void new_food();

    virtual void add_head(pos head);

    virtual void remove_back();

    std::deque<pos> snake;

    // returns true if the player is still alive, false otherwise
    virtual bool tick(Move move);

    Game();
};

enum Field {
    EMPTY,
    FOOD,
    SNAKE,
    WALL
};

class VisualizedGame : public Game {
public:
    WINDOW* window;
    void set_field(pos pos1, Field field);

    void new_food() override;

    void add_head(pos head) override;

    void remove_back() override;

    bool tick(Move move) override;

    VisualizedGame();
    ~VisualizedGame() {
        endwin();
    }

};

#endif //SNAKEAI_GAME_H

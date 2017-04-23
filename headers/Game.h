#pragma once 

#include <memory>
#include <SFML/Graphics.hpp>
#include "EventManager.h"
#include "Window.h"
#include "Board.h"

class Board;
class Game {
public:
    Game();

    void setup();
    void update();
    void render();
    std::shared_ptr<Window> getWindow() const;
    void restartClock();
    void increaseScore(int lines);
    void lose();

    static const int BLOCKS_HOR = 10;
    static const int BLOCKS_VERT = 20;
    static const int WINDOW_WIDTH = 500;
    static const int WINDOW_HEIGHT = 600;
    static const int BLOCK_SIZE = 30;
    static const int TOP_SPEED = 25;
    static const int LEVEL_STEP = 3000;

private:
    void attachCallbacks();
    void checkIncreaseLevel();
    void arrowUp(EventDetails*);
    void arrowLeft(EventDetails*);
    void arrowRight(EventDetails*);
    void speedUp(EventDetails*);
    void speedDown(EventDetails*);

    std::shared_ptr<EventManager> eventManager;
    std::shared_ptr<Window> window;
    std::shared_ptr<Board> board;
    sf::Clock clock;
    sf::Time elapsed;
    int score = 0;
    int level = 1;
    int speed;
    bool lost = false;
    bool keyDownPressed = false;
};

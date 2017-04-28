#pragma once 

#include <memory>
#include <SFML/Graphics.hpp>
#include "constants.h"
#include "EventManager.h"
#include "Window.h"
#include "Board.h"
#include "Transform.h"

class Board;
class Figure;
class Transform;
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

    private:
    void attachCallbacks();
    void checkIncreaseLevel();
    void arrowUp(EventDetails*);
    void arrowLeft(EventDetails*);
    void arrowRight(EventDetails*);
    void speedUp(EventDetails*);
    void speedDown(EventDetails*);
    void genFigure();
    void genNextFigure();

    std::shared_ptr<EventManager> eventManager;
    std::shared_ptr<Window> window;
    std::shared_ptr<Board> board;
    std::shared_ptr<Transform> transform;
    std::shared_ptr<Figure> currentFigure;
    std::shared_ptr<Figure> nextFigure;
    sf::Clock clock;
    sf::Time elapsed;
    int score = 0;
    int level = 1;
    int speed;
    bool lost = false;
    bool keyDownPressed = false;
};

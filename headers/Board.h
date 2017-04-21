#pragma once

#include <array>
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "Window.h"
#include "Game.h"
#include "Figure.h"

struct BoardBlock {
    BoardBlock(sf::Color c) : color(c), exists(true) {}
    BoardBlock() : exists(false) {}
    sf::Color color;
    bool exists;
};

class Figure;
class Window;
class Game;
class Board {
public:
    explicit Board(std::shared_ptr<Window> window);

    void update();
    void render(const int, const int);
    void rotate();
    void onLeft();
    void onRight();
private:
    void drawGrid();
    void genFigure();
    void renderBlocks();
    void explodeFigure();
    bool isCollided() const;
    void drawLabels(const int, const int);
    void drawText(sf::Text &label, const std::string text, const int offsetX, const int offsetY);
    bool checkSideMovePossible(const int offset) const;

    std::shared_ptr<Window> window;
    std::shared_ptr<Figure> currentFigure;
    sf::Font font;
    sf::Text score;
    sf::Text level;
    sf::RectangleShape rect;
    std::array<std::array<std::shared_ptr<BoardBlock>, 10>, 20> grid;
};

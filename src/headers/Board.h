#pragma once

#include <array>
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "constants.h"
#include "Window.h"
#include "Game.h"
#include "Figure.h"

struct BoardBlock {
    BoardBlock(sf::Color c) : color(c), exists(true) {}
    BoardBlock() : exists(false) {}
    sf::Color color;
    bool exists;
};

using Grid = std::array<std::array<std::shared_ptr<BoardBlock>, BLOCKS_HOR>, BLOCKS_VERT>;

class Figure;
class Window;
class Game;
class Board {
    public:
    explicit Board(std::shared_ptr<Window> window);

    void update();
    void render();
    Grid getGrid() const;
    void setGrid(const Grid grid);
    int getFullLines();

    private:
    void drawGrid();
    void renderBlocks();

    std::shared_ptr<Window> window;
    sf::RectangleShape rect;
    Grid mGrid;
};

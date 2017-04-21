#pragma once

#include <array>
#include <SFML/Graphics.hpp>
#include "Game.h"

const sf::Color FigureColors[7] = {
    sf::Color(248, 196, 50),
    sf::Color(230, 105, 205),
    sf::Color(255, 146, 33),
    sf::Color(155, 224, 31),
    sf::Color(40,  107, 239),
    sf::Color(6,   183, 255),
    sf::Color(252, 44,  72)
};

const std::array<std::array<int, 16>, 14> FigureBlocks = {{
    {0,0,0,0, 1,1,1,0, 1,0,0,0, 0,0,0,0}, // Hammer
    {0,0,0,0, 1,1,1,0, 0,0,1,0, 0,0,0,0}, // Hammer
    {0,0,1,0, 0,0,1,0, 0,1,1,0, 0,0,0,0}, // Hammer
    {0,1,0,0, 0,1,0,0, 0,1,1,0, 0,0,0,0}, // Hammer
    {0,0,0,0, 1,1,0,0, 0,1,1,0, 0,0,0,0}, // Dog
    {0,0,0,0, 0,1,1,0, 1,1,0,0, 0,0,0,0}, // Dog
    {0,1,0,0, 0,1,1,0, 0,0,1,0, 0,0,0,0}, // Dog
    {0,0,1,0, 0,1,1,0, 0,1,0,0, 0,0,0,0}, // Dog
    {0,0,0,0, 0,1,0,0, 1,1,1,0, 0,0,0,0}, // Submarine
    {0,0,1,0, 0,1,1,0, 0,0,1,0, 0,0,0,0}, // Submarine
    {0,1,0,0, 0,1,1,0, 0,1,0,0, 0,0,0,0}, // Submarine
    {0,0,0,0, 0,0,0,0, 1,1,1,1, 0,0,0,0}, // Line
    {0,1,0,0, 0,1,0,0, 0,1,0,0, 0,1,0,0}, // Line
    {0,0,0,0, 0,1,1,0, 0,1,1,0, 0,0,0,0}  // Cube
}};

class Game;
class Figure {
public:
    explicit Figure(std::shared_ptr<Window> w, sf::Vector2u c);
    void render();
    void update();
    void destroy();
    void rotate();
    void onLeft();
    void onRight();
    sf::Color getColor() const;
    sf::Vector2u getCoords() const;
    std::array<int, 16> getBlocks() const;
private:
    std::shared_ptr<Window> window;
    sf::Vector2u coords;
    std::array<int, 16> blocks;
    sf::Color color;
    sf::RectangleShape rect;
};

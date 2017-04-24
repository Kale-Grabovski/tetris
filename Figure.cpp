#include <iostream>
#include "headers/Figure.h"

Figure::Figure(std::shared_ptr<Window> w, sf::Vector2u c) : window(w), coords(c) {
    blocks = FigureBlocks[rand() % FigureBlocks.size()];
    color  = FigureColors[rand() % sizeof(FigureColors) / sizeof(sf::Color)];

    // -1 to make the padding between blocks
    rect.setSize(sf::Vector2f(Game::BLOCK_SIZE - 1, Game::BLOCK_SIZE - 1));
}

void Figure::update() {
    ++coords.y;
}

void Figure::toLeft() {
    --coords.x;
}

void Figure::toRight() { 
    ++coords.x; 
}

sf::Color Figure::getColor() const { return color; }

std::array<int, 16> Figure::getBlocks() const { return blocks; }
void Figure::setBlocks(std::array<int, 16> blocks_) { blocks = blocks_; }

sf::Vector2u Figure::getCoords() const { return coords; }
void Figure::setCoords(sf::Vector2u coords_) { coords = coords_; }

void Figure::render() {
    for (int i = 0; i < 16; i++) {
        if (blocks[i] == 1) {
            rect.setFillColor(color);
            rect.setPosition(coords.x * Game::BLOCK_SIZE + (i % 4) * Game::BLOCK_SIZE,
                coords.y * Game::BLOCK_SIZE + ((int)i / 4) * Game::BLOCK_SIZE);
            window->draw(rect); 
        }
    }
}

void Figure::destroy() {
    for (int i = 0; i < 16; i++) {
        blocks[i] = 0;
    }
}

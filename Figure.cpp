#include <iostream>
#include "headers/Figure.h"

Figure::Figure(std::shared_ptr<Window> w, sf::Vector2u c) : window(w), coords(c) {
    blocks = FigureBlocks[0];
    color  = FigureColors[1];

    // -1 to make the padding between blocks
    rect.setSize(sf::Vector2f(Game::BLOCK_SIZE - 1, Game::BLOCK_SIZE - 1));
}

void Figure::update() {
    ++coords.y;
}

void Figure::destroy() {
    for (int i = 0; i < 16; i++) {
        blocks[i] = 0;
    }
}

void Figure::rotate() {
    std::array<int, 16> rotatedBlocks;

    // Rotate the figure
    for (int i = 0; i < 4; i++) {
        for (int k = 0; k < 4; k++) {
            rotatedBlocks[i * 4 + k] = blocks[16 - 4 * (k + 1) + i];
        }
    }

    blocks = rotatedBlocks;
}

void Figure::onLeft() {
    for (int i = 0; i < 16; i++) {
        if (blocks[i] == 1 && coords.x + i % 4 == 0) {
            return;
        }
    }

    // Shift the figure borders so the don't cross the left board
    if (coords.x == 0) {
        std::array<int, 16> shiftedBlocks;

        for (int i = 0; i < 4; i++) {
            for (int k = 0; k < 4; k++) {
                shiftedBlocks[i * 4 + k] = (k == 3 ? 0 : blocks[4 * i + k + 1]);
            }
        }

        blocks = shiftedBlocks;
        return;
    }

    --coords.x;
}

void Figure::onRight() {
    for (int i = 0; i < 16; i++) {
        if (blocks[i] == 1 && coords.x + i % 4 == Game::BLOCKS_HOR - 1) {
            return;
        }
    }

    // Shift the figure borders so the don't cross the right board
    if (coords.x == Game::BLOCKS_HOR - 4) {
        std::array<int, 16> shiftedBlocks;

        for (int i = 0; i < 4; i++) {
            for (int k = 0; k < 4; k++) {
                shiftedBlocks[i * 4 + k] = (k == 0 ? 0 : blocks[4 * i + k - 1]);
            }
        }

        blocks = shiftedBlocks;
        return;
    }

    ++coords.x;
}

sf::Vector2u Figure::getCoords() const { return coords; }
std::array<int, 16> Figure::getBlocks() const { return blocks; }
sf::Color Figure::getColor() const { return color; }

void Figure::render() {
    for (int i = 0; i < 16; i++) {
        if (blocks[i] == 1) {
            rect.setFillColor(color);
            rect.setPosition(coords.x * Game::BLOCK_SIZE + (i % 4) * Game::BLOCK_SIZE,
                coords.y * Game::BLOCK_SIZE + ((int)i / 4) * Game::BLOCK_SIZE);
            window->draw(rect); 
        } else {
            rect.setFillColor(sf::Color(44, 22, 180));
            rect.setPosition(coords.x * Game::BLOCK_SIZE + (i % 4) * Game::BLOCK_SIZE,
                coords.y * Game::BLOCK_SIZE + ((int)i / 4) * Game::BLOCK_SIZE);
            window->draw(rect); 
        }
    }
}

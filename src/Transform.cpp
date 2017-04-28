#include <iostream>
#include "headers/Transform.h"

Transform::Transform(std::shared_ptr<Board> board) : mBoard(board) {}

void Transform::rotate(FigurePtr figure) const {
    std::array<int, 16> blocks = figure->getBlocks();
    std::array<int, 16> rotatedBlocks;

    // Rotate the figure
    for (int i = 0; i < 4; i++) {
        for (int k = 0; k < 4; k++) {
            rotatedBlocks[i * 4 + k] = blocks[16 - 4 * (k + 1) + i];
        }
    }

    // Check on collisions with border blocks
    if (!hasCollisionsWithBlocks(figure, rotatedBlocks)) {
        figure->setBlocks(rotatedBlocks);
    }
}

bool Transform::hasCollisionsWithBlocks(const FigurePtr figure, const std::array<int, 16> blocks) const {
    auto grid = mBoard->getGrid();
    sf::Vector2u coords = figure->getCoords();

    for (int i = 0; i < BLOCKS_VERT; i++) {
        for (int k = 0; k < BLOCKS_HOR; k++) {
            for (int b = 0; b < 16; b++) {
                int x = (int)b / 4 + coords.y;
                int y = b % 4 + coords.x;

                if (x >= 0 && y >= 0 && blocks[b] == 1 && grid[x][y]->exists) {
                    return true;
                }
            }
        }
    }

    return false;
}

void Transform::toLeft(FigurePtr figure) const {
    sf::Vector2u coords = figure->getCoords();
    std::array<int, 16> blocks = figure->getBlocks();

    if (isSideMovePossible(coords, blocks, -1)) {
        if (coords.x == 0) {
            shiftFigureBordersRight(coords, blocks);
            return figure->setBlocks(blocks);
        }

        figure->toLeft();
    }
}

void Transform::toRight(FigurePtr figure) const {
    sf::Vector2u coords = figure->getCoords();
    std::array<int, 16> blocks = figure->getBlocks();

    if (isSideMovePossible(coords, blocks, 1)) {
        if (coords.x == BLOCKS_HOR - 4) {
            shiftFigureBordersLeft(coords, blocks);
            return figure->setBlocks(blocks);
        }

        figure->toRight();
    }
}

// Shift the figure borders so the don't cross the left board border
void Transform::shiftFigureBordersRight(const sf::Vector2u coords, std::array<int, 16>& blocks) const {
    std::array<int, 16> shiftedBlocks;

    for (int i = 0; i < 4; i++) {
        for (int k = 0; k < 4; k++) {
            shiftedBlocks[i * 4 + k] = (k == 3 ? 0 : blocks[4 * i + k + 1]);
        }
    }

    blocks = shiftedBlocks;
}


// Shift the figure borders so the don't cross the right board border
void Transform::shiftFigureBordersLeft(const sf::Vector2u coords, std::array<int, 16>& blocks) const {
    std::array<int, 16> shiftedBlocks;

    for (int i = 0; i < 4; i++) {
        for (int k = 0; k < 4; k++) {
            shiftedBlocks[i * 4 + k] = (k == 0 ? 0 : blocks[4 * i + k - 1]);
        }
    }

    blocks = shiftedBlocks;
}

// Check the collision with the right/left blocks
bool Transform::isSideMovePossible(const sf::Vector2u coords, 
    const std::array<int, 16> blocks, const int offset) const {
    auto grid = mBoard->getGrid();

    if (offset == -1) {
        // Check if we cross left border
        for (int i = 0; i < 16; i++) {
            if (blocks[i] == 1 && coords.x + i % 4 == 0) {
                return false;
            }
        }
    } else {
        // Check if we cross right border
        for (int i = 0; i < 16; i++) {
            if (blocks[i] == 1 && coords.x + i % 4 == BLOCKS_HOR - 1) {
                return false;
            }
        }
    }

    // Check if we could collide with another blocks on the board
    for (int i = 0; i < 16; i++) {
        int x = (int)i / 4 + coords.y;
        int y = i % 4 + coords.x + offset;

        if (x >= 0 && y >= 0 && blocks[i] == 1 && grid[x][y]->exists) {
            return false;
        }
    }

    return true;
}

// Explode figure blocks on board block and then destroy the figure
bool Transform::explodeFigure(const FigurePtr figure) const {
    auto grid = mBoard->getGrid();
    sf::Vector2u coords = figure->getCoords();
    std::array<int, 16> blocks = figure->getBlocks();
    bool isSuccess = true;

    for (int i = 0; i < 16; i++) {
        if (blocks[i] == 0) {
            continue;
        }

        int y = (int)i / 4 + coords.y;
        int x = i % 4 + coords.x;

        // Turn figure block into grid block
        if (y >= 0) {
            grid[y][x] = std::make_shared<BoardBlock>(figure->getColor());
        }

        // Out of the top border of the board
        if (y <= 0) {
            isSuccess = false;
        }
    }

    mBoard->setGrid(grid);
    figure->destroy();

    return isSuccess;
}

bool Transform::isCollided(FigurePtr figure) const {
    auto grid = mBoard->getGrid();
    sf::Vector2u coords = figure->getCoords();
    std::array<int, 16> blocks = figure->getBlocks();

    // Check if we touch the bottom edge
    for (uint s = 0; s < 16; s++) {
        if (blocks[s] == 1 && (int)s / 4 + coords.y == BLOCKS_VERT - 1) {
            return true;
        }
    }

    // Iterate through grid blocks to check if we touch another blocks
    for (uint i = 0; i < BLOCKS_VERT; i++) {
        for (uint k = 0; k < BLOCKS_HOR; k++) {

            // Iterate through current figure to check position of each block
            for (uint s = 0; s < 16; s++) {
                if (blocks[s] == 1 && 
                    grid[i][k]->exists &&
                    k == s % 4 + coords.x && // check x-coords are equal
                    i - 1 == (int)s / 4 + coords.y) { // check if figure block is above grid block
                    return true;
                }
            }
        }
    }

    return false;
}

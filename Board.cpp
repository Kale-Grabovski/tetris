#include <iostream>
#include "headers/Board.h"

Board::Board(std::shared_ptr<Window> w) : window(w) {
    font.loadFromFile("arial.ttf");
    rect.setSize(sf::Vector2f(Game::BLOCK_SIZE - 1, Game::BLOCK_SIZE - 1));

    // Fill out the grid with zeros
    for (int i = 0; i < Game::BLOCKS_VERT; i++) {
        for (int k = 0; k < Game::BLOCKS_HOR; k++) {
            grid[i][k] = std::make_shared<BoardBlock>();
        }
    }

    genFigure();
}

void Board::genFigure() {
    currentFigure = std::make_shared<Figure>(window, sf::Vector2u(3, -3));
}

void Board::update() {
    if (isCollided()) {
        explodeFigure();
        genFigure();
    }

    currentFigure->update();
}

void Board::rotate() {
    currentFigure->rotate();
}

void Board::onLeft() {
    if (checkSideMovePossible(-1)) {
        currentFigure->onLeft();
    }
}

void Board::onRight() {
    if (checkSideMovePossible(1)) {
        currentFigure->onRight();
    }
}

// Check the collision with the right/left blocks
bool Board::checkSideMovePossible(const int offset) const {
    sf::Vector2u coords = currentFigure->getCoords();
    std::array<int, 16> blocks = currentFigure->getBlocks();

    for (int i = 0; i < 16; i++) {
        int x = (int)i / 4 + coords.y;
        int y = i % 4 + coords.x + offset;

        if (x >= 0 && y >= 0 && blocks[i] == 1 && grid[x][y]->exists) {
            return false;
        }
    }

    return true;
}

void Board::explodeFigure() {
    // todo: duplicates
    sf::Vector2u coords = currentFigure->getCoords();
    std::array<int, 16> blocks = currentFigure->getBlocks();

    // Turn the current figure into separated board blocks
    for (int i = 0; i < 16; i++) {
        if (blocks[i] == 1) {
            grid[(int)i / 4 + coords.y][i % 4 + coords.x] = std::make_shared<BoardBlock>(currentFigure->getColor());
        }
    }

    currentFigure->destroy();
}

void Board::renderBlocks() {
    for (int i = 0; i < Game::BLOCKS_VERT; i++) {
        for (int k = 0; k < Game::BLOCKS_HOR; k++) {
            if (grid[i][k]->exists) {
                rect.setFillColor(grid[i][k]->color);
                rect.setPosition(k * Game::BLOCK_SIZE, i * Game::BLOCK_SIZE);
                window->draw(rect); 
            }
        }
    }
}

bool Board::isCollided() const {
    sf::Vector2u coords = currentFigure->getCoords();
    std::array<int, 16> blocks = currentFigure->getBlocks();

    // Check if we touch the bottom edge
    for (uint s = 0; s < 16; s++) {
        if (blocks[s] == 1 && (int)s / 4 + coords.y == Game::BLOCKS_VERT - 1) {
            return true;
        }
    }

    // Iterate through grid blocks to check if we touch another blocks
    for (uint i = 0; i < Game::BLOCKS_VERT; i++) {
        for (uint k = 0; k < Game::BLOCKS_HOR; k++) {

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

void Board::render(const int gameScore, const int gameLevel) {
    drawLabels(gameScore, gameLevel);
    drawGrid();
    renderBlocks();
    currentFigure->render();
}

void Board::drawText(sf::Text &label, const std::string text, const int offsetX, const int offsetY) {
    label.setPosition(window->getSize().x / 2 + offsetX, offsetY);
    label.setFont(font);
    label.setString(text);
    label.setCharacterSize(20);

    window->draw(label);
}

void Board::drawLabels(const int gameScore, const int gameLevel) {
    sf::Text scoreLabel;
    sf::Text levelLabel;
    sf::Text nextLabel;

    drawText(scoreLabel, "Score:", 70, 20);
    drawText(levelLabel, "Level:", 71, 50);
    drawText(nextLabel,  "Next:",  70, 80);

    drawText(score, std::to_string(gameScore), 135, 20);
    drawText(level, std::to_string(gameLevel), 135, 50);
}

void Board::drawGrid() {
    // 2 times larger because we need two points to draw one line
    sf::VertexArray horLines(sf::Lines, Game::BLOCKS_VERT * 2);
    sf::VertexArray vertLines(sf::Lines, Game::BLOCKS_HOR * 2);
    sf::RectangleShape border;

    for (uint i = 0; i < Game::BLOCKS_VERT; i++) {
        horLines[i * 2].position = sf::Vector2f(0, Game::BLOCK_SIZE * i);
        horLines[i * 2].color = sf::Color(50, 50, 50);
        horLines[i * 2 + 1].position = sf::Vector2f(Game::BLOCK_SIZE * Game::BLOCKS_HOR, Game::BLOCK_SIZE * i);
        horLines[i * 2 + 1].color = sf::Color(50, 50, 50);
    }

    for (uint i = 0; i < Game::BLOCKS_HOR; i++) {
        vertLines[i * 2].position = sf::Vector2f(Game::BLOCK_SIZE * i, 0);
        vertLines[i * 2].color = sf::Color(50, 50, 50);
        vertLines[i * 2 + 1].position = sf::Vector2f(Game::BLOCK_SIZE * i, Game::BLOCK_SIZE * Game::BLOCKS_VERT);
        vertLines[i * 2 + 1].color = sf::Color(50, 50, 50);
    }

    // Draw border line
    border.setSize(sf::Vector2f(2, Game::BLOCK_SIZE * Game::BLOCKS_VERT));
    border.setFillColor(sf::Color(100, 100, 100));
    border.setPosition(Game::BLOCK_SIZE * Game::BLOCKS_HOR, 0);

    window->draw(horLines);
    window->draw(vertLines);
    window->draw(border);
}


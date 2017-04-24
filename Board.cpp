#include <iostream>
#include "headers/Board.h"

Board::Board(std::shared_ptr<Window> w) : window(w) {
    font.loadFromFile("arial.ttf");
    rect.setSize(sf::Vector2f(Game::BLOCK_SIZE - 1, Game::BLOCK_SIZE - 1));

    // Fill out the grid with zeros
    for (int i = 0; i < Game::BLOCKS_VERT; i++) {
        for (int k = 0; k < Game::BLOCKS_HOR; k++) {
            mGrid[i][k] = std::make_shared<BoardBlock>();
        }
    }
}

Grid Board::getGrid() const { return mGrid; }
void Board::setGrid(const Grid grid) { mGrid = grid; }

void Board::update() {}

void Board::renderBlocks() {
    for (int i = 0; i < Game::BLOCKS_VERT; i++) {
        for (int k = 0; k < Game::BLOCKS_HOR; k++) {
            if (mGrid[i][k]->exists) {
                rect.setFillColor(mGrid[i][k]->color);
                rect.setPosition(k * Game::BLOCK_SIZE, i * Game::BLOCK_SIZE);
                window->draw(rect);
            }
        }
    }
}

void Board::render(const int gameScore, const int gameLevel) {
    drawLabels(gameScore, gameLevel);
    drawGrid();
    renderBlocks();
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


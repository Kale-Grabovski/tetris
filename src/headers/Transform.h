#pragma once

#include <memory>
#include "constants.h"
#include "Board.h"

class Board;
class Figure;

using FigurePtr = std::shared_ptr<Figure>;

class Transform {
    public:
    explicit Transform(std::shared_ptr<Board>);

    void rotate(FigurePtr figure) const;
    void toLeft(FigurePtr figure) const;
    void toRight(FigurePtr figure) const;
    bool isCollided(FigurePtr figure) const;
    bool explodeFigure(FigurePtr figure) const;

    private:
    std::shared_ptr<Board> mBoard;
    bool rotatePossible() const;
    bool isSideMovePossible(const sf::Vector2u coords, const std::array<int, 16> blocks, const int offset) const;
    bool hasCollisionsWithBlocks(const FigurePtr figure, const std::array<int, 16> blocks) const;
    void shiftFigureBordersLeft(const sf::Vector2u coords, std::array<int, 16>& blocks) const;
    void shiftFigureBordersRight(const sf::Vector2u coords, std::array<int, 16>& blocks) const;
};

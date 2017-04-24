#pragma once

#include <memory>
#include "Board.h"

class Board;
class Figure;

using BoardPtr  = std::shared_ptr<Board>;
using FigurePtr = std::shared_ptr<Figure>;

class Transform {
    public:
    void rotate(const BoardPtr board, FigurePtr figure) const;
    void toLeft(const BoardPtr board, FigurePtr figure) const;
    void toRight(const BoardPtr board, FigurePtr figure) const;
    bool isCollided(const BoardPtr board, FigurePtr figure) const;
    bool explodeFigure(const BoardPtr board, FigurePtr figure) const;
    int getFullLines(BoardPtr board) const;

    private:
    bool rotatePossible() const;
    bool isSideMovePossible(const BoardPtr board, const sf::Vector2u coords, 
        const std::array<int, 16> blocks, const int offset) const;
    void shiftFigureBordersLeft(const sf::Vector2u coords, std::array<int, 16>& blocks) const;
    void shiftFigureBordersRight(const sf::Vector2u coords, std::array<int, 16>& blocks) const;
};

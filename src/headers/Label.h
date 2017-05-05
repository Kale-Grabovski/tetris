#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "Window.h"

class Window;
class Label {
    public:
    explicit Label(std::shared_ptr<Window> window);
    void render(const int score, const int level, const bool isPause, const bool isGameOver);
    void switchPause();

    private:
    void drawText(sf::Text label, std::string text, int offsetX, int offsetY, int charSize = 20);
    std::shared_ptr<Window> mWindow;
    sf::Font font;
    sf::Text scoreValue;
    sf::Text levelValue;
};

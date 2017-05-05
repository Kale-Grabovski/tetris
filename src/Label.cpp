#include "headers/Label.h"

Label::Label(std::shared_ptr<Window> window) : mWindow(window) {
    font.loadFromFile("arial.ttf");
}

void Label::render(const int score, const int level, const bool isPause, const bool isGameOver) {
    sf::Text scoreLabel;
    sf::Text levelLabel;
    sf::Text nextLabel;
    sf::Text pauseLabel;

    drawText(scoreLabel, "Score:", 70, 20);
    drawText(levelLabel, "Level:", 71, 50);
    drawText(nextLabel,  "Next:",  70, 80);
    drawText(scoreValue, std::to_string(score), 135, 20);
    drawText(levelValue, std::to_string(level), 135, 50);

    if (isPause) {
        pauseLabel.setFillColor(sf::Color(223, 181, 59));
        drawText(pauseLabel, "Pause", 70, 240, 40);
    }

    if (isGameOver) {
        pauseLabel.setFillColor(sf::Color(223, 21, 39));
        drawText(pauseLabel, "Game Over", 70, 240, 30);
    }
}

void Label::drawText(sf::Text label, std::string text, int offsetX, int offsetY, int charSize) {
    label.setPosition(mWindow->getSize().x / 2 + offsetX, offsetY);
    label.setFont(font);
    label.setString(text);
    label.setCharacterSize(charSize);

    mWindow->draw(label);
}

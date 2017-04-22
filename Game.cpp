#include <iostream>
#include <time.h>
#include "headers/Game.h"

Game::Game() 
    : eventManager(std::make_shared<EventManager>()),
    window(std::make_shared<Window>(eventManager, "Tetris", sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT))),
    board(std::make_shared<Board>(window)),
    speed(level) {}

void Game::attachCallbacks() {
    eventManager->addCallback("Arrow_up", &Game::arrowUp, this);
    eventManager->addCallback("Arrow_left", &Game::arrowLeft, this);
    eventManager->addCallback("Arrow_right", &Game::arrowRight, this);
    eventManager->addCallback("Arrow_down", &Game::speedUp, this);
    eventManager->addCallback("Arrow_down_released", &Game::speedDown, this);
}

void Game::arrowUp(EventDetails*) { board->rotate(); }
void Game::arrowLeft(EventDetails*) { board->onLeft(); }
void Game::arrowRight(EventDetails*) { board->onRight(); }
void Game::speedUp(EventDetails*) { speed = TOP_SPEED; }
void Game::speedDown(EventDetails*) { speed = level; }

void Game::setup() {
    attachCallbacks();
    srand(time(NULL));
}

void Game::update() {
    sf::Time timestep = sf::seconds(0.7f / speed);

    if (elapsed >= timestep) {
        int lines = board->update();
        if (lines > 0) {
            increaseScore(lines);
        }

        elapsed -= timestep;
    }

    window->update();
}

void Game::render() {
    window->beginDraw();
    board->render(score, level);
    window->endDraw();
}

std::shared_ptr<Window> Game::getWindow() const { return window; }

void Game::restartClock() {
    elapsed += clock.restart();
}

void Game::increaseScore(int lines) {
    int points;

    switch (lines) {
        case 1: points = 100; break;
        case 2: points = 300; break;
        case 3: points = 900; break;
        case 4: points = 1500; break;
    }

    score += points * level;

    checkIncreaseLevel();
}

void Game::checkIncreaseLevel() {
    if (score >= LEVEL_STEP * ( level == 1 ? 1 : 2 << (level - 1) )) {
        level++;
    }
}

void Game::lose() {}

#include <iostream>
#include <time.h>
#include "headers/Game.h"

Game::Game() 
    : eventManager(std::make_shared<EventManager>()),
    window(std::make_shared<Window>(eventManager, "Tetris", sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT))),
    board(std::make_shared<Board>(window)),
    transform(std::make_shared<Transform>()),
    speed(level) {}

void Game::attachCallbacks() {
    eventManager->addCallback("Arrow_up", &Game::arrowUp, this);
    eventManager->addCallback("Arrow_left", &Game::arrowLeft, this);
    eventManager->addCallback("Arrow_right", &Game::arrowRight, this);
    eventManager->addCallback("Arrow_down", &Game::speedUp, this);
    eventManager->addCallback("Arrow_down_released", &Game::speedDown, this);
}

void Game::arrowUp(EventDetails*) { transform->rotate(board, currentFigure); }
void Game::arrowLeft(EventDetails*) { transform->toLeft(board, currentFigure); }
void Game::arrowRight(EventDetails*) { transform->toRight(board, currentFigure); }

void Game::speedDown(EventDetails*) { 
    speed = level; 
    keyDownPressed = false; 
}

void Game::speedUp(EventDetails*) { 
    // This method fired somehow after some time if we hold down key, 
    // so we need this flag to prevent timer reset second time
    if (!keyDownPressed) {
        speed = TOP_SPEED; 
        elapsed = sf::Time();
        keyDownPressed = true;
    }
}

void Game::setup() {
    srand(time(NULL));
    attachCallbacks();
    genNextFigure();
    genFigure();
}

void Game::genNextFigure() {
    nextFigure = std::make_shared<Figure>(window, sf::Vector2u(11, 4));
}

void Game::genFigure() {
    currentFigure = nextFigure;
    currentFigure->setCoords(sf::Vector2u(3, -3));
    genNextFigure();
}

void Game::update() {
    sf::Time timestep = sf::seconds(1.0f / speed);

    if (elapsed >= timestep) {
        if (transform->isCollided(board, currentFigure)) {
            if (!transform->explodeFigure(board, currentFigure)) {
                // todo: Stop timer here or something
                lost = true;
            } else {
                int lines = transform->getFullLines(board);
                if (lines > 0) {
                    increaseScore(lines);
                }

                genFigure();
            }
        }

        currentFigure->update();

        elapsed -= timestep;
    }

    window->update();
}

void Game::render() {
    window->beginDraw();
    board->render(score, level);
    currentFigure->render();
    nextFigure->render();
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

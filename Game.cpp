#include <iostream>
#include "headers/Game.h"

Game::Game() 
    : eventManager(std::make_shared<EventManager>()),
    window(std::make_shared<Window>(eventManager, "Tetris", sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT))),
    board(std::make_shared<Board>(window)) { 
    attachCallbacks();
}

void Game::attachCallbacks() {
    eventManager->addCallback("Arrow_up", &Game::arrowUp, this);
    eventManager->addCallback("Arrow_left", &Game::arrowLeft, this);
    eventManager->addCallback("Arrow_right", &Game::arrowRight, this);
    eventManager->addCallback("Arrow_down", &Game::speedUp, this);
}

void Game::arrowUp(EventDetails*) { board->rotate(); }
void Game::arrowLeft(EventDetails*) { board->onLeft(); }
void Game::arrowRight(EventDetails*) { board->onRight(); }

void Game::speedUp(EventDetails*) { 

}

void Game::setup() {
    time(NULL);
}

void Game::update() {
    sf::Time timestep = sf::seconds(1.0f / level);

    if (elapsed >= timestep) {
        board->update();
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

sf::Time Game::getElapsed() const {
    return elapsed;
}

void Game::restartClock() {
    elapsed += clock.restart();
}

void Game::increaseScore() {
    score += 10;
}

void Game::lose() {}

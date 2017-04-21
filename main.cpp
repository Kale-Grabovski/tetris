#include <memory>
#include "headers/Game.h"

int main(int argc, char* argv[]) {
    std::shared_ptr<Game> game(new Game());
    game->setup();

    while (!game->getWindow()->getIsDone()) {
        game->update();
        game->render();
        game->restartClock();
    }

    return 0;
}

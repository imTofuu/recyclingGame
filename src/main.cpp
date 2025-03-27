#include "Game.h"

int main() {

    // This is the main game object which contains the window and the
    // game scene.
    RecyclingGame::Game game;

    // Set the instance of game so that it can be allocated in stack memory and
    // gotten from other places
    RecyclingGame::Game::setInstance(&game);

    // This initializes essential parts of the game such as the graphics
    // API and the window. It also contains the main game loop.
    game.init();

    // Once the game has finished, game::init() will return and this will
    // clean resources and end the game.
    game.end();
    
}

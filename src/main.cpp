#include "Game.h"

int main()
{
    SnakeGame::Game game(20, 20);
    game.initialize();
    game.run();
}
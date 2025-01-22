#include "Game.h"
#include <iostream>

int main()
{
    SnakeGame::Game game(20, 20);
    if (game.initialize())
    {
        std::cerr << "Failed to initialize game." << std::endl;
        std::cin.get();
        return -1;
    }
    game.run();
}
#include "Game.h"

#include <glm/glm.hpp>

namespace SnakeGame
{

    Game::Game(int width, int height)
    {
        createApple();
    }

    void Game::moveSnake()
    {
        
    }

    bool Game::checkHeadHit()
    {
        /*for (int i = 1; i < m_Snake.size(); i++)
        {
            if (m_Snake[0].getPos() == m_Snake[i].getPos())
                return true;
        }*/
        return false;
    }

    bool Game::checkWin()
    {
        //return m_Snake.size() == (m_FieldWidth * m_FieldHeight);
        return 0;
    }

    void Game::eatApple()
    {
        
    }

    void Game::createApple()
    {
        // TODO: сделать генерацию, чтобы не пересекалось со змейкой
    }

    void Game::draw()
    {

    }

} // SnakeGame
#include "Game.h"

#include <glm/glm.hpp>

namespace SnakeGame
{

    Render2D Game::s_Renderer;

    Game::Game(int width, int height)
    {
        m_Snake.reserve(width * height);
        m_Snake.emplace_back(glm::ivec2(rand() % width, rand() % height), glm::ivec2(rand() % 2, rand() % 2));
        m_Snake.emplace_back(m_Snake[0]);
        createApple();
    }

    void Game::moveSnake()
    {
        m_Snake[0].move();
        for (int i = 1; i < m_Snake.size(); i++)
        {
            m_Snake[i].move(m_Snake[i - 1]);
        }
    }

    bool Game::checkHeadHit()
    {
        for (int i = 1; i < m_Snake.size(); i++)
        {
            if (m_Snake[0].getPos() == m_Snake[i].getPos())
                return true;
        }
        return false;
    }

    bool Game::checkWin()
    {
        return m_Snake.size() == (m_FieldWidth * m_FieldHeight);
    }

    void Game::eatApple()
    {
        m_Snake.emplace_back(m_Snake.back());
    }

    void Game::createApple()
    {
        // TODO: сделать генерацию, чтобы не пересекалось со змейкой
    }

    void Game::draw()
    {

    }

} // SnakeGame
#include "Game.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <chrono>
#include <time.h>

#include <glm/glm.hpp>
#include <iostream>

#include <queue>

namespace SnakeGame
{

    Game::Game(int width, int height)
        : m_FieldWidth(width), m_FieldHeight(height), m_Snake(width * height)
    {
    }

    int Game::initialize()
    {
        if (m_Window.initialize(m_FieldWidth * m_TileSize, m_FieldHeight * m_TileSize, "Snake"))
        {
            std::cerr << "Unable to initialize Window" << std::endl;
            return -1;
        }

        if (m_Events.bindWindow(m_Window))
        {
            std::cerr << "Failed to bind window\n";
            return -1;
        }

        if (Snake::initRenderer())
        {
            std::cerr << "Uneable to initialize Render2D: Snake" << std::endl;
            return -1;
        }

        if (m_Renderer.initialize())
        {
            std::cerr << "Uneable to initialize Render2D: Game" << std::endl;
            return -1;
        }

        restart();
        createApple();
    }

    void Game::run()
    {
        auto timer = std::chrono::high_resolution_clock::now();
        bool tick = false;
        int end = 0;

        srand(time(0));

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        while (!m_Window.shouldClose())
        {
            m_Events.pollIvents();

            if (end == 1)
            {
                std::cout << "You win!" << std::endl;
                std::cout << "Restart game? (y / n)" << std::endl;
                if (std::cin.get() == 'y')
                {
                    restart();
                }
                else
                {
                    m_Window.setShouldClose(true);
                }
            }
            else if (end == 2)
            {
                std::cout << "You lose!" << std::endl;
                std::cout << "Restart game? (y / n)" << std::endl;
                if (std::cin.get() == 'y')
                {
                    restart();
                }
                else
                {
                    m_Window.setShouldClose(true);
                }
            }

            //auto now = std::chrono::high_resolution_clock::now();
            //auto timeLast = std::chrono::milliseconds(m_MovePeriod * 55 / 100);
            if (m_Events.keyJPressed(GLFW_KEY_UP) && m_Snake.headDir().y == 0)
            {
                if (userInputs.empty() || (userInputs.size() < 2 && userInputs.front() != UP /*&& now - timer <= timeLast)*/))
                    userInputs.push(UP);
            }
            else if (m_Events.keyJPressed(GLFW_KEY_DOWN) && m_Snake.headDir().y == 0)
            {
                if (userInputs.empty() || (userInputs.size() < 2 && userInputs.front() != DOWN /*&& now - timer <= timeLast)*/))
                    userInputs.push(DOWN);
            }
            else if (m_Events.keyJPressed(GLFW_KEY_RIGHT) && m_Snake.headDir().x == 0)
            {
                if (userInputs.empty() || (userInputs.size() < 2 && userInputs.front() != RIGHT /*&& now - timer <= timeLast)*/))
                    userInputs.push(RIGHT);
            }
            else if (m_Events.keyJPressed(GLFW_KEY_LEFT) && m_Snake.headDir().x == 0)
            {
                if (userInputs.empty() || (userInputs.size() < 2 && userInputs.front() != LEFT /*&& now - timer <= timeLast)*/))
                    userInputs.push(LEFT);
            }

            if (m_Events.keyPressed(GLFW_KEY_SPACE))
            {
                m_MovePeriod = 200;
            }
            if (m_Events.keyReleased(GLFW_KEY_SPACE))
            {
                m_MovePeriod = 350;
            }

            if (std::chrono::high_resolution_clock::now() - timer >= std::chrono::milliseconds(m_MovePeriod))
            {
                applyHeadTurn();
                m_Snake.moveForward(m_FieldWidth, m_FieldHeight);
                tick = true;
                timer = std::chrono::high_resolution_clock::now();
            }

            if (tick)
            {
                if (m_Snake.headPos() == m_ApplePos)
                {
                    m_Snake.grow();
                    createApple();
                }
                if (checkWin())
                {
                    end = 1;
                    continue;
                }
                else if (checkHeadHit())
                {
                    end = 2;
                    continue;
                }
                tick = false;
            }

            drawApple();
            m_Snake.draw(m_Window, m_TileSize);
            m_Window.swapBuffers();

            m_Window.clearScreen();
        }
        m_Window.terminate();
    }

    void Game::restart()
    {
        /*int x = rand() % (m_FieldWidth - 1) + 1;
        int y = rand() % (m_FieldHeight - 1) + 1;
        glm::vec2 dir = glm::vec2(m_FieldWidth / 2, m_FieldHeight / 2) - glm::vec2(x, y);
        dir /= std::max(dir.x, dir.y);
        if (abs(dir.x) < 1 && abs(dir.y) < 1) dir = glm::vec2(1, 0);
        m_Snake.createSnake(x, y, (int)dir.x, (int)dir.y);*/

        m_Snake.createSnake(4, m_FieldHeight / 2, 1, 0);
    }

    void Game::setFieldWidth(int width)
    {
        m_FieldWidth = width;
    }

    void Game::setFieldHeigt(int height)
    {
        m_FieldHeight = height;
    }

    void Game::setTilePixelSize(int tileSize)
    {
        m_TileSize = tileSize;
    }

    bool Game::checkHeadHit()
    {
        if (m_Snake.headPos().x < 0 || m_Snake.headPos().x >= m_FieldWidth
            || m_Snake.headPos().y < 0 || m_Snake.headPos().y > m_FieldHeight)
            return true;
        for (auto& i : m_Snake)
        {
            if (m_Snake.headPos() == i.getPos())
                return true;
        }
        return false;
    }

    bool Game::checkWin()
    {
        return m_Snake.size() == (m_FieldWidth * m_FieldHeight);
    }

    void Game::createApple()
    {
        if (checkWin()) return;
        do
        {
            m_ApplePos.x = rand() % m_FieldWidth;
            m_ApplePos.y = rand() % m_FieldHeight;
        } while (checkAppleCollision());
    }

    bool Game::checkAppleCollision()
    {
        if (m_Snake.headPos() == m_ApplePos) return true;
        for (auto& i : m_Snake)
        {
            if (i.getPos() == m_ApplePos) return true;
        }
        return false;
    }

    void Game::drawApple()
    {
        m_Renderer.drawBox(m_ApplePos * glm::ivec2(m_TileSize) + glm::ivec2(m_TileSize / 2), m_TileSize - 3, m_TileSize - 3, 1.0f, { 1, 0, 0 }, m_Window);
    }

    void Game::applyHeadTurn()
    {
        if (userInputs.empty()) return;
        Directions nextTurn = userInputs.front();
        userInputs.pop();
        if (nextTurn == UP && m_Snake.headDir().y == 0)
        {
            if (m_Snake.headDir().x == 1) m_Snake.turnLeft();
            else m_Snake.turnRight();
        }
        else if (nextTurn == DOWN && m_Snake.headDir().y == 0)
        {
            if (m_Snake.headDir().x == -1) m_Snake.turnLeft();
            else m_Snake.turnRight();
        }
        else if (nextTurn == RIGHT && m_Snake.headDir().x == 0)
        {
            if (m_Snake.headDir().y == 1) m_Snake.turnLeft();
            else m_Snake.turnRight();
        }
        else if (nextTurn == LEFT && m_Snake.headDir().x == 0)
        {
            if (m_Snake.headDir().y == -1) m_Snake.turnLeft();
            else m_Snake.turnRight();
        }
    }

} // SnakeGame
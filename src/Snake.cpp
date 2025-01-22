#include "Snake.h"

#include "Consts.h"

namespace SnakeGame
{

    /*const glm::imat2x2 ROT_MAT_CLKWS = { 0, 1, -1, 0 };
    const glm::imat2x2 ROT_MAT_ANTI_CLKWS = { 0, -1, 1, 0 };*/

    //=====================================[SnakeBody]=====================================//

    SnakeBody::SnakeBody(const glm::ivec2& position, const glm::ivec2& direction)
        : m_Position(position), m_Direction(direction)
    {
    }

    SnakeBody::SnakeBody(const SnakeBody& tail)
        : m_Direction(tail.getDir()), m_Position(tail.getPos())
    {
    }

    void SnakeBody::move(int width, int height)
    {
        m_Position += m_Direction;
        if (m_Position.x >= width) m_Position.x = 0;
        else if (m_Position.x < 0) m_Position.x = width - 1;
        else if (m_Position.y >= height) m_Position.y = 0;
        else if (m_Position.y < 0) m_Position.y = height - 1;
    }

    void SnakeBody::move(const SnakeBody& next, int width, int height)
    {
        m_Position += m_Direction;
        m_Direction = next.getPos() - m_Position;

        if (m_Position.x >= width) m_Position.x = 0;
        else if (m_Position.x < 0) m_Position.x = width - 1;
        else if (m_Position.y >= height) m_Position.y = 0;
        else if (m_Position.y < 0) m_Position.y = height - 1;
    }

    void SnakeBody::turnRight()
    {
        glm::imat2x2 ROT_MAT_CLKWS = { 0, -1, 1, 0 };
        m_Direction = m_Direction * ROT_MAT_CLKWS;
    }

    void SnakeBody::turnLeft()
    {
        glm::imat2x2 ROT_MAT_ANTI_CLKWS = { 0, 1, -1, 0 };
        m_Direction = m_Direction * ROT_MAT_ANTI_CLKWS;
    }

    const glm::ivec2& SnakeBody::getPos() const
    {
        return m_Position;
    }

    const glm::ivec2& SnakeBody::getDir() const
    {
        return m_Direction;
    }

    //=====================================[Snake]=====================================//

    Render2D Snake::s_Renderer;

    Snake::Snake(int reserve)
    {
        m_Body.reserve(reserve);
    }

    int Snake::initRenderer()
    {
        return s_Renderer.initialize();
    }

    void Snake::createSnake(int x, int y, int dirX, int dirY)
    {
        m_Body.clear();
        m_Body.emplace_back(glm::ivec2(x, y), glm::ivec2(dirX, dirY));
        m_Body.emplace_back(glm::ivec2(x, y) - glm::ivec2(dirX, dirY), glm::ivec2(dirX, dirY));
        m_LastTailState = m_Body.back();
    }

    void Snake::draw(const Window& window, int tileSize) const
    {
        s_Renderer.drawBox(headPos() * glm::ivec2(tileSize) + glm::ivec2(tileSize / 2), tileSize - 3, tileSize - 3, 1.0f, { 0, 1, 0 }, window);
        for (auto& i : *this)
        {
            s_Renderer.drawBox(i.getPos() * glm::ivec2(tileSize) + glm::ivec2(tileSize / 2), tileSize - 3, tileSize - 3, 1.0f, {0, 1, 0}, window);
        }
        s_Renderer.drawBox(
            headPos() * glm::ivec2(tileSize) + glm::ivec2(tileSize / 2) + (headDir() * (tileSize / 2)),
            ((tileSize - 3) / 2), ((tileSize - 3) / 2),
            1.0f, { 1, 0, 0 }, window
        );
    }

    void Snake::moveForward(int width, int height)
    {
        m_LastTailState = m_Body.back();
        m_Body[0].move(width, height);
        for (int i = 1; i < m_Body.size(); i++)
        {
            m_Body[i].move(m_Body[i - 1], width, height);
        }
    }

    void Snake::grow()
    {
        m_Body.emplace_back(m_LastTailState);
    }

    void Snake::turnRight()
    {
        m_Body[0].turnRight();
    }

    void Snake::turnLeft()
    {
        m_Body[0].turnLeft();
    }

    int Snake::size() const
    {
        return m_Body.size();
    }

    const glm::ivec2& Snake::headPos() const
    {
        return m_Body[0].getPos();
    }

    const glm::ivec2& Snake::headDir() const
    {
        return m_Body[0].getDir();
    }

    Snake::SnakeIterator Snake::begin()
    {
        return ++m_Body.begin();
    }

    Snake::SnakeIterator Snake::end()
    {
        return m_Body.end();
    }

    Snake::const_SnakeIterator Snake::begin() const
    {
        return ++m_Body.begin();
    }

    Snake::const_SnakeIterator Snake::end() const
    {
        return m_Body.end();
    }

} // SnakeGame
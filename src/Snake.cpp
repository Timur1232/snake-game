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
        : m_Direction(tail.getDir()), m_Position(tail.getPos() - tail.getDir())
    {
    }

    void SnakeBody::move()
    {
        m_Position += m_Direction;
    }

    void SnakeBody::move(const SnakeBody& next)
    {
        m_Position += m_Direction;
        m_Direction = next.getPos() - m_Position;
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

    Snake::Snake()
    {
        m_Body.reserve(TILES_AMOUNT);
    }

    int Snake::initRenderer()
    {
        return s_Renderer.initialize();
    }

    void Snake::createSnake(int x, int y, int dirX, int dirY)
    {
        m_Body.emplace_back(glm::ivec2(x, y), glm::ivec2(dirX, dirY));
        m_Body.emplace_back(m_Body[0]);
    }

    void Snake::draw(const Window& window) const
    {
        for (auto& i : m_Body)
        {
            s_Renderer.drawBox(i.getPos() * glm::ivec2(TILE_SIDE_SIZE / 2) + glm::ivec2(TILE_SIDE_SIZE / 4), TILE_SIDE_SIZE - 3, TILE_SIDE_SIZE - 3, 1.0f, {0, 1, 0}, window);
        }
    }

    void Snake::moveForward()
    {
        m_Body[0].move();
        for (int i = 1; i < m_Body.size(); i++)
        {
            m_Body[i].move(m_Body[i - 1]);
        }
    }

    void Snake::grow()
    {
        m_Body.emplace_back(m_Body.back());
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

} // SnakeGame
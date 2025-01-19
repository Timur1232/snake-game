#include "SnakeBody.h"

namespace SnakeGame
{
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

    const glm::ivec2& SnakeBody::getPos() const
    {
        return m_Position;
    }

    const glm::ivec2& SnakeBody::getDir() const
    {
        return m_Direction;
    }

} // SnakeGame
#pragma once

#include <glm/glm.hpp>

namespace SnakeGame
{

    class SnakeBody
    {
    public:
        SnakeBody() = default;
        SnakeBody(const glm::ivec2& position, const glm::ivec2& direction);
        SnakeBody(const SnakeBody& tail);

        void move();
        void move(const SnakeBody& next);

        const glm::ivec2& getPos() const;
        const glm::ivec2& getDir() const;

    private:
        glm::ivec2 m_Position = { 0, 0 };
        glm::ivec2 m_Direction = { 0, 0 };
    };

} // SnakeGame
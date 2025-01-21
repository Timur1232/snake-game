#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "graphics/Render2D.h"
#include "Window.h"

namespace SnakeGame
{

    //extern const glm::imat2x2 ROT_MAT_CLKWS;
    //extern const glm::imat2x2 ROT_MAT_ANTI_CLKWS;

    class SnakeBody
    {
    public:
        SnakeBody() = default;
        SnakeBody(const glm::ivec2& position, const glm::ivec2& direction);
        SnakeBody(const SnakeBody& tail);

        void move();
        void move(const SnakeBody& next);

        void turnRight();
        void turnLeft();

        const glm::ivec2& getPos() const;
        const glm::ivec2& getDir() const;

    private:
        glm::ivec2 m_Position = { 0, 0 };
        glm::ivec2 m_Direction = { 0, 0 };
    };

    class Snake
    {
    public:
        using SnakeIterator = std::vector<SnakeBody>::iterator;
        using const_SnakeIterator = std::vector<SnakeBody>::const_iterator;

    public:
        Snake();
        //Snake(int xPos, int yPos);

        static int initRenderer();
        void createSnake(int x, int y, int dirX, int dirY);

        void draw(const Window& window) const;
        void moveForward();
        void grow();
        void turnRight();
        void turnLeft();

        int size() const;
        const glm::ivec2& headPos() const;
        const glm::ivec2& headDir() const;

        SnakeIterator begin();
        SnakeIterator end();

        const_SnakeIterator begin() const;
        const_SnakeIterator end() const;

    private:
        std::vector<SnakeBody> m_Body;
        static Render2D s_Renderer;
    };

} // SnakeGame
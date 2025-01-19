#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "SnakeBody.h"
#include "graphics/Render2D.h"

namespace SnakeGame
{

    class Game
    {
    public:
        Game() = delete;
        Game(int width, int height);

        void run();
        //void restart();

    private:
        void moveSnake();
        bool checkHeadHit();
        bool checkWin();
        void eatApple();
        void createApple();

        void draw();

    private:
        std::vector<SnakeBody> m_Snake;
        glm::ivec2 m_ApplePos = { 0, 0 };
        int m_FieldWidth;
        int m_FieldHeight;
        static Render2D s_Renderer;
    };

} // SnakeGame
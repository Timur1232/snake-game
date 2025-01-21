#pragma once

#include <vector>
#include <queue>
#include <glm/glm.hpp>
#include "Snake.h"
#include "Window.h"
#include "Events.h"
#include "graphics/Render2D.h"

namespace SnakeGame
{

    class Game
    {
    private:
        enum Directions
        {
            UP, DOWN,
            LEFT, RIGHT
        };

    public:
        Game() = delete;
        Game(int width, int height);

        int initialize();
        void run();
        void restart();

        void setFieldWidth(int width);
        void setFieldHeigt(int height);
        void setTilePixelSize(int tileSize);

    private:
        bool checkHeadHit();
        bool checkWin();
        void createApple();
        bool checkAppleCollision();
        void drawApple();
        void applyHeadTurn();

    private:
        Snake m_Snake;
        glm::ivec2 m_ApplePos = { 0, 0 };

        std::queue<Directions> userInputs;

        int m_FieldWidth;
        int m_FieldHeight;
        int m_TileSize = 22;
        int m_MovePeriod = 350; // milliseconds

        Window m_Window;
        Events m_Events;
        Render2D m_Renderer;
    };

} // SnakeGame
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <chrono>

#include "Consts.h"

#include "graphics/Render2D.h"
#include "Window.h"
#include "Events.h"
#include <iostream>

#include "Snake.h"

using namespace SnakeGame;

#if 1
int main()
{
    Window window;
    if (window.initialize(500, 500, "Snake"))
    {
        std::cerr << "Uneable to initialize Window" << std::endl;
        return -1;
    }

    Events events;
    if (events.bindWindow(window))
    {
        std::cerr << "Failed to bind window\n";
        return -1;
    }

    Render2D renderer;
    if (renderer.initialize())
    {
        std::cerr << "Uneable to initialize Render2D" << std::endl;
        return -1;
    }

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    while (!window.shouldClose())
    {
        events.pollIvents();
        renderer.drawBox({ 125, 125 }, 250, 250, 1.0f, { 0, 1, 0 }, window);
        //renderer.drawBox({ 250, 250 }, 35, 35, 0.0001f, { 1, 0.8, 1 }, window);
        window.swapBuffers();
        window.clearScreen();
    }
    window.terminate();
    
    //std::cin.get();
}
#else

int main()
{
    Window window;
    if (window.initialize(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake"))
    {
        std::cerr << "Uneable to initialize Window" << std::endl;
        return -1;
    }

    Events events;
    if (events.bindWindow(window))
    {
        std::cerr << "Failed to bind window\n";
        return -1;
    }

    if (Snake::initRenderer())
    {
        std::cerr << "Uneable to initialize Render2D" << std::endl;
        return -1;
    }

    Snake snake;
    snake.createSnake(5, 1, 0, 1);

    auto timer = std::chrono::high_resolution_clock::now();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    while (!window.shouldClose())
    {
        events.pollIvents();

        // FIXME: при быстром нажимании подряд любую комбинацию соседних стрелок (вверх-направо, вниз-влево и тд) змея заползает сам в себя
        // FIXME: инпут лаг
        if (events.keyJPressed(GLFW_KEY_UP) && snake.headDir().y == 0)
        {
            if (snake.headDir().x == 1) snake.turnLeft();
            else snake.turnRight();
            //snake.moveForward();
        }
        else if (events.keyJPressed(GLFW_KEY_DOWN) && snake.headDir().y == 0)
        {
            if (snake.headDir().x == -1) snake.turnLeft();
            else snake.turnRight();
            //snake.moveForward();
        }
        else if (events.keyJPressed(GLFW_KEY_RIGHT) && snake.headDir().x == 0)
        {
            if (snake.headDir().y == 1) snake.turnLeft();
            else snake.turnRight();
            //snake.moveForward();
        }
        else if (events.keyJPressed(GLFW_KEY_LEFT) && snake.headDir().x == 0)
        {
            if (snake.headDir().y == -1) snake.turnLeft();
            else snake.turnRight();
            //snake.moveForward();
        }
        else if (events.keyJPressed(GLFW_KEY_SPACE))
        {
            snake.grow();
        }
        
        if (std::chrono::high_resolution_clock::now() - timer >= std::chrono::milliseconds(500))
        {
            snake.moveForward();
            timer = std::chrono::high_resolution_clock::now();
        }

        snake.draw(window);

        window.swapBuffers();
        window.clearScreen();
    }
    window.terminate();
}

#endif
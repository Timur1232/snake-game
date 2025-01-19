#pragma once

#include "Events.h"

struct GLFWwindow;

namespace SnakeGame
{

class Window
{
public:
	Window() = default;

	int initialize(int width, int height, const char* title);
	void terminate();

	bool shouldClose() const;
	int getWidth() const;
	int getHeight() const;
	GLFWwindow* getWindowPtr() const;

	void setShouldClose(bool flag);
	void swapBuffers() const;
	void clearScreen() const;

private:
	GLFWwindow* m_Window = nullptr;
	int m_Width = 0;
	int m_Height = 0;
	static bool sm_Initialized;
};

} // SnakeGame

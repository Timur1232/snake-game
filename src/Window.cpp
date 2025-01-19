#include "Window.h"

#include <iostream>
#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "Events.h"

namespace SnakeGame
{

bool Window::sm_Initialized = false;

int Window::initialize(int width, int height, const char* title)
{
	if (!sm_Initialized)
	{
		glewExperimental = GL_TRUE;

		if (!glfwInit())
		{
			return -1;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	}

	m_Window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if (!m_Window)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(m_Window);

	if (!sm_Initialized)
	{
		if (glewInit() != GLEW_OK)
		{
			std::cerr << "Failed to initialize GLEW" << std::endl;
			glfwTerminate();
			return -1;
		}
	}

	glViewport(0, 0, width, height);
	m_Width = width;
	m_Height = height;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	sm_Initialized = true;
	return 0;
}

void Window::terminate()
{
	glfwTerminate();
}

bool Window::shouldClose() const
{
	return glfwWindowShouldClose(m_Window);
}

void Window::setShouldClose(bool flag)
{
	glfwSetWindowShouldClose(m_Window, flag);
}

void Window::swapBuffers() const
{
	glfwSwapBuffers(m_Window);
}

int Window::getWidth() const
{
	return m_Width;
}

int Window::getHeight() const
{
	return m_Height;
}

GLFWwindow* Window::getWindowPtr() const
{
	return m_Window;
}

void Window::clearScreen() const
{
	glClear(GL_COLOR_BUFFER_BIT);
}

} // SnakeGame
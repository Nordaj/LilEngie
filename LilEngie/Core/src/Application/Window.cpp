#include <iostream>

#include <GLFW/glfw3.h>

#include "Game.h"
#include "Window.h"

void Window::Init()
{
	//Init glfw
	if (!glfwInit())
	{
		std::cout << "Could not init glfw" << std::endl;
		std::cin.get();
		//TODO: I dont want to go up a level here, 
		//need better error handling
		Game::Close();
		return;
	}

	//Create window
	window = glfwCreateWindow(width, height, title, NULL, NULL);
	glfwMakeContextCurrent(window);
}

bool Window::Open()
{
	return !glfwWindowShouldClose(window);
}

void Window::SwapBuffers()
{
	glfwSwapBuffers(window);
}

void Window::PollEvents()
{
	glfwPollEvents();
}

void Window::Close()
{
	glfwTerminate();
}

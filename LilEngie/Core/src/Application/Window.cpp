#include <iostream>
#include <GLFW/glfw3.h>
#include <Game/Game.h>
#include <Application/Debug.h>
#include <Input/Input.h>
#include <Graphics/Renderer.h>
#include "Window.h"

//Properites
namespace Window
{
	//Public
	int width = 1280;
	int height = 720;
	char title[] = "My Game";

	//Private
	GLFWwindow *window;
}

void Resize(GLFWwindow *win, int width, int height)
{
	Renderer::Resize(width, height);
	Window::width = width;
	Window::height = height;
}

void Window::Init()
{
	//Init glfw
	if (!glfwInit())
	{
		ERROR("Could not init glfw");
		std::cin.get();
		//TODO: I dont want to go up a level here, 
		//need better error handling
		Game::Close();
		return;
	}

	//Create window
	window = glfwCreateWindow(width, height, title, NULL, NULL);
	glfwMakeContextCurrent(window);

	//Setup resize callback
	glfwSetFramebufferSizeCallback(window, Resize);

	//Init input
	Input::Init(window);
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
	glfwDestroyWindow(window);
}

void Window::Clean()
{
	glfwTerminate();
}

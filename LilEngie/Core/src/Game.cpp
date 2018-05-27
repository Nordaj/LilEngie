#include <iostream>

#include <GL/glew.h>

#include "Application/Window.h"
#include "Graphics/Renderer.h"
#include "Game.h"

void Game::Init()
{
	Window::Init();
	Renderer::Init();
}

void Game::Run()
{
	while (Window::Open())
	{
		Renderer::Render();
		Window::SwapBuffers();
		Window::PollEvents();
	}
}

void Game::Close()
{
	Window::Close();
}

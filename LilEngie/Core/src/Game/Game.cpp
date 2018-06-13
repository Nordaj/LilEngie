#include <iostream>

#include <GL/glew.h>

#include <Application/Window.h>
#include <Graphics/Renderer.h>
#include <Entity/ObjectManager.h>
#include "Game.h"

void Game::Init()
{
	Window::Init();
	Renderer::Init();
}

void Game::Run(vFunction callback)
{
	ObjectManager::Start();

	while (Window::Open())
	{
		ObjectManager::Update();

		if (callback != nullptr)
			callback();

		Renderer::Render();
		Window::SwapBuffers();
		Window::PollEvents();
	}
}

void Game::Close()
{
	Window::Close();
}

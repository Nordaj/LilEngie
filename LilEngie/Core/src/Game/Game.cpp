#include <iostream>

#include <GL/glew.h>

#include <Application/Window.h>
#include <Graphics/Renderer.h>
#include <Graphics/ModelHandler.h>
#include <Entity/ObjectManager.h>
#include "Game.h"

void Game::Init()
{
	Window::Init();
	Renderer::Init();
}

void Game::Run(vFunction callback)
{
	while (Window::Open() && !closing)
	{
		ObjectManager::Update();

		if (callback != nullptr)
			callback();

		Renderer::Render();
		Window::SwapBuffers();
		Window::PollEvents();
	}

	ObjectManager::GetCurrent()->Close();
	Window::Close();
	Window::Clean();
}

void Game::Close()
{
	closing = true;
}

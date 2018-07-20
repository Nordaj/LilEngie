#include <iostream>

#include <GL/glew.h>

#include <Application/Window.h>
#include <Application/Time.h>
#include <Graphics/Renderer.h>
#include <Graphics/ModelHandler.h>
#include <Entity/SceneManager.h>
#include "Game.h"

//Properties
namespace Game
{
	//Private
	bool closing;
}

void Game::Init()
{
	Window::Init();
	Renderer::Init();
}

void Game::Run(vFunction callback)
{
	while (Window::Open() && !closing)
	{
		Time::StartFrame();

		SceneManager::Update();

		if (callback != nullptr)
			callback();

		Renderer::Render();
		Window::SwapBuffers();
		Window::PollEvents();

		Time::EndFrame();
	}

	Scenes::Close();
	Window::Close();
	Window::Clean();
}

void Game::Close()
{
	closing = true;
}

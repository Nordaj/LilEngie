#include <iostream>
#include <Application/Window.h>
#include <Application/Time.h>
#include <Graphics/Renderer.h>
#include <Graphics/ModelHandler.h>
#include <Entity/SceneManager.h>
#include <Input/Input.h>
#include "Game.h"

//Properties
namespace Game
{
	//Private
	bool closing;
}

void Game::Init(vFunction callback)
{
	Window::Init();
	Renderer::Init();
	Input::Init();

	if (callback != nullptr)
		callback();
}

void Game::Run(vFunction callback)
{
	//Change to update input, poll events, then update scene

	while (Window::Open() && !closing)
	{
		Time::StartFrame();

		//Update all behaviour
		SceneManager::Update();
		if (callback != nullptr)
			callback();

		Input::Update();

		Renderer::Render();

		Window::PollEvents();
		Window::SwapBuffer();

		Time::EndFrame();
	}

	Scenes::Close();
	Window::Close();
	Window::Clean();
}

void Game::Close()
{
	Renderer::Shutdown();
	closing = true;
}

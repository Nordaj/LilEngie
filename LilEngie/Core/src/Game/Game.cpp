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

void Game::Run()
{
	ObjectManager::Start();

	while (Window::Open())
	{
		ObjectManager::Update();
		Renderer::Render();
		Window::SwapBuffers();
		Window::PollEvents();
	}
}

void Game::Close()
{
	Window::Close();
}

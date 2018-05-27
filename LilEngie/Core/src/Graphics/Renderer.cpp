#include <iostream>

#include <GL/glew.h>

#include "Game.h"
#include "Renderer.h"

void Renderer::SetClearColor(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
}

void Renderer::Init()
{
	//Init glew
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to init glew" << std::endl;
		std::cin.get();
		//TODO: I dont want to go up a level here, 
		//need better error handling
		Game::Close();
	}
}

void Renderer::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

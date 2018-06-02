#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <Entity/Components/Mesh.h>
#include "MeshRenderer.h"
#include "Game.h"
#include "Renderer.h"

void Renderer::SetClearColor(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
}

void Renderer::AddMesh(Mesh &mesh)
{
	meshes.push_back(&mesh);
}

void Renderer::Init()
{
	//Init glew
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to init glew" << std::endl;
		std::cin.get();
		Game::Close();
	}
}

void Renderer::Render()
{
	//Clear
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Render each mesh
	for (int i = 0; i < meshes.size(); i++)
	{
		MeshRenderer *r = meshes[i]->GetRenderer();
		glm::mat4 *t = meshes[i]->GetTransformation();
		r->Draw(*t);
	}
}

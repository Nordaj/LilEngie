#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <Entity/Components/Mesh.h>
#include <Entity/Components/Camera.h>
#include "MeshRenderer.h"
#include "Game.h"
#include "Renderer.h"

Camera* Renderer::GetCurrentCamera()
{
	return currentCamera;
}

void Renderer::SetClearColor(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
}

void Renderer::SetCurrentCamera(Camera *cam)
{
	currentCamera = cam;
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

	currentCamera = nullptr;
}

void Renderer::Render()
{
	//Clear
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Render each mesh
	for (int i = 0; i < meshes.size(); i++)
	{
		glm::mat4 MVP;

		//Calculate MVP
		if (currentCamera != nullptr)
		{
			glm::mat4 &M = *meshes[i]->GetTransformation();
			glm::mat4 &V = currentCamera->GetView();
			glm::mat4 &P = currentCamera->GetProjection();
			MVP = P * V * M;
		}
		else
		{
			MVP = *meshes[i]->GetTransformation();
		}

		//Render
		MeshRenderer *r = meshes[i]->GetRenderer();
		r->Draw(MVP);
	}
}

#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <Entity/Components/Mesh.h>
#include <Entity/Components/Camera.h>
#include "UniformHandler.h"
#include "MaterialHandler.h"
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

	//glPolygonMode(GL_FRONT, GL_LINE);
	glEnable(GL_DEPTH_TEST);
}

void Renderer::Render()
{
	//Clear
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Render each mesh
	for (int i = 0; i < meshes.size(); i++)
	{
		if (currentCamera != nullptr)
		{
			glm::mat4 &V = currentCamera->GetView();
			glm::mat4 &P = currentCamera->GetProjection();
			meshes[i]->Draw(V, P);
		}
		else
		{
			glm::mat4 v = glm::mat4(1);
			glm::mat4 p = glm::mat4(1);
			meshes[i]->Draw(v, p);
		}
	}
}

#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <Entity/Components/Mesh.h>
#include <Entity/Components/Camera.h>
#include <Game/Game.h>
#include "UniformHandler.h"
#include "MaterialHandler.h"
#include "MeshRenderer.h"
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

	//Setup defualt texture
	glGenTextures(1, &defaultTex);
	glBindTexture(GL_TEXTURE_2D, defaultTex);
	char tex[] = { 255, 255, 255, 255 };
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//Clear the current cam
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
		//Clear out current texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, defaultTex);

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

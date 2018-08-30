#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <Entity/Components/Mesh.h>
#include <Entity/Components/Camera.h>
#include <Entity/Scene.h>
#include <Game/Game.h>
#include <Application/Debug.h>
#include "Text/TextHandler.h"
#include "UniformHandler.h"
#include "MaterialHandler.h"
#include "MeshRenderer.h"
#include "Renderer.h"

//Properties
namespace Renderer
{
	//Private
	Scene *scene;
	unsigned int defaultTex;
}

Camera* Renderer::GetCurrentCamera()
{
	return scene->GetCam();
}

void Renderer::SetScene(Scene *s)
{
	scene = s;
}

void Renderer::SetClearColor(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
}

void Renderer::Init()
{
	unsigned int result = glewInit();

	//Init glew
	if (glewInit() != GLEW_OK)
	{
		ERROR("Failed to init glew");
		Game::Close();
	}

	//Init text renderer
	TextHandler::Init();

	//Setup defualt texture
	glGenTextures(1, &defaultTex);
	glBindTexture(GL_TEXTURE_2D, defaultTex);
	char tex[] = { 255, 255, 255, 255 };
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//glPolygonMode(GL_FRONT, GL_LINE);
	glEnable(GL_DEPTH_TEST);

	//Blending mode
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::Render()
{
	//Clear
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Render each mesh
	for (int i = 0; i < scene->GetQueue()->size(); i++)
	{
		//Clear out current texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, defaultTex);

		if (scene->GetCam() != nullptr)
		{
			glm::mat4 &V = scene->GetCam()->GetView();
			glm::mat4 &P = scene->GetCam()->GetProjection();
			(*scene->GetQueue())[i]->Draw(V, P, scene->GetCam()->GetTransform()->position);
		}
		else
		{
			glm::mat4 v = glm::mat4(1);
			glm::mat4 p = glm::mat4(1);
			glm::vec3 origin;
			(*scene->GetQueue())[i]->Draw(v, p, origin);
		}
	}

	//Transparency stuff
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);

	//Render text last
	scene->texts.Render();

	//Undo blending stuff
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
}

void Renderer::Resize(int width, int height)
{
	glViewport(0, 0, width, height);
}

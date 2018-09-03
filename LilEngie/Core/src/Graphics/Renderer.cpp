#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <Platform/Gfx.h>
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
	Gfx::SetClearColor(r, g, b, a);
}

void Renderer::Init()
{
	//Init glew
	if (!Gfx::InitRenderer())
	{
		ERROR("Failed to init graphics renderer");
		Game::Close();
	}

	Gfx::CreateDefaultTex(&defaultTex);
	Gfx::SetBlendingMode(Gfx::BlendFunction::SrcAlpha, Gfx::BlendFunction::OneMinusSrcAlpha);
	Gfx::DepthTest(true);

	//Init text renderer
	TextHandler::Init();
}

void Renderer::Render()
{
	//Clear
	Gfx::ClearFrame();

	//Render each mesh
	for (int i = 0; i < scene->GetQueue()->size(); i++)
	{
		//Clear out current texture
		Gfx::BindTexture(defaultTex, 0);

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
	Gfx::DepthTest(false);
	Gfx::Blending(true);

	//Render text last
	scene->texts.Render();

	//Undo blending stuff
	Gfx::Blending(false);
	Gfx::DepthTest(true);
}

void Renderer::Resize(int width, int height)
{
	Gfx::Viewport(0, 0, width, height);
}

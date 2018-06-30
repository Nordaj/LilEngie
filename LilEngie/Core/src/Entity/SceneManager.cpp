#include <vector>
#include <Graphics/Renderer.h>
#include <Entity/Components/Camera.h>
#include "GameObject.h"
#include "Scene.h"
#include "SceneManager.h"

//Properties
namespace SceneManager
{
	//Private
	Scene *scene;
}

void SceneManager::SetScene(Scene *s)
{
	if (scene != nullptr)
		scene->Close();

	scene = s;
	Start();
	
	Renderer::SetScene(scene);
}

Scene* SceneManager::GetCurrent()
{
	return scene;
}

void SceneManager::SetCurrentCamera(Camera *cam)
{
	scene->SetCurrentCamera(cam);
}

void SceneManager::Start()
{
	if (scene != nullptr)
		scene->Start();
}

void SceneManager::Update()
{
	if (scene != nullptr)
		scene->Update();
}

bool SceneManager::CheckScene()
{
	return scene != nullptr;
}
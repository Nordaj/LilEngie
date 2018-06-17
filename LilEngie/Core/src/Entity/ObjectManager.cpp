#include <vector>
#include <Graphics/Renderer.h>
#include <Entity/Components/Camera.h>
#include "GameObject.h"
#include "Scene.h"
#include "ObjectManager.h"

void ObjectManager::SetScene(Scene *s)
{
	if (scene != nullptr)
		scene->Close();

	scene = s;
	Start();
	
	Renderer::SetScene(scene);
}

Scene* ObjectManager::GetCurrent()
{
	return scene;
}

void ObjectManager::SetCurrentCamera(Camera *cam)
{
	scene->SetCurrentCamera(cam);
}

void ObjectManager::Start()
{
	if (scene != nullptr)
		scene->Start();
}

void ObjectManager::Update()
{
	if (scene != nullptr)
		scene->Update();
}

bool ObjectManager::CheckScene()
{
	return scene != nullptr;
}

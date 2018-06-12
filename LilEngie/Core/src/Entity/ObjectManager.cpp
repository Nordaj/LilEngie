#include <vector>
#include "GameObject.h"
#include "Scene.h"
#include "ObjectManager.h"

void ObjectManager::SetScene(Scene *s)
{
	if (scene != nullptr)
		scene->Close();

	scene = s;
	Start();
}

void ObjectManager::AddObjectToCurrent(GameObject &obj)
{
	if (scene != nullptr)
		scene->AddObject(obj);
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

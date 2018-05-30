#include <vector>
#include "GameObject.h"
#include "ObjectManager.h"

void ObjectManager::AddObject(GameObject &obj)
{
	objects.push_back(&obj);
}

void ObjectManager::Start()
{
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Start();
	}
}

void ObjectManager::Update()
{
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update();
	}
}

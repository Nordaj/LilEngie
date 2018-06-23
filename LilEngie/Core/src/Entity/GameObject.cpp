#include <iostream>
#include <vector>
#include <string>
#include <Application/Debug.h>
#include "SceneManager.h"
#include "Component.h"
#include "GameObject.h"

GameObject::GameObject(Scene *scene)
{
	if (scene == nullptr)
		LOG("Give your object a scene, cunt");

	myScene = scene;
}

GameObject::~GameObject()
{
	for (int i = 0; i < components.size(); i++)
		delete components[i];
}

void GameObject::AddComponent(void *comp)
{
	components.push_back((Component*)comp);
}

void* GameObject::GetComponent(std::string comp)
{
	for (int i = 0; i < components.size(); i++)
	{
		if (components[i]->GetType() == comp)
			return components[i]->Get();
	}

	LOG("Could not find component");
	return nullptr;
}

Scene* GameObject::GetMyScene()
{
	return myScene;
}

void GameObject::Start()
{
	for (int i = 0; i < components.size(); i++)
		components[i]->Start();
}

void GameObject::Update()
{
	for (int i = 0; i < components.size(); i++)
		components[i]->Update();
}

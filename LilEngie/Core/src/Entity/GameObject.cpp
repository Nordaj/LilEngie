#include <iostream>
#include <vector>
#include <string>
#include "ObjectManager.h"
#include "Component.h"
#include "GameObject.h"

GameObject::GameObject(Scene *scene)
{
	if (scene == nullptr)
		std::cout << "Give your object a scene, cunt" << std::endl;

	myScene = scene;
}

void GameObject::AddComponent(Component &comp)
{
	components.push_back(&comp);
}

void* GameObject::GetComponent(std::string comp)
{
	for (int i = 0; i < components.size(); i++)
	{
		if (components[i]->GetType() == comp)
			return components[i]->Get();
	}

	std::cout << "Could not find component" << std::endl;
	return nullptr;
}

Scene* GameObject::GetMyScene()
{
	return myScene;
}

void GameObject::Start()
{
	for (int i = 0; i < components.size(); i++)
	{
		components[i]->Start();
	}
}

void GameObject::Update()
{
	for (int i = 0; i < components.size(); i++)
	{
		components[i]->Update();
	}
}

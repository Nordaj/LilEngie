#include <iostream>
#include <vector>
#include <string>
#include "ObjectManager.h"
#include "Component.h"
#include "GameObject.h"

GameObject::GameObject(Scene *scene)
{
	if (scene == nullptr)
		ObjectManager::AddObjectToCurrent(*this);
	else
		scene->AddObject(*this);
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

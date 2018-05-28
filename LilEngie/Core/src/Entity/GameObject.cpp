#include <vector>
#include <string>
#include "Component.h"
#include "GameObject.h"

void GameObject::AddComponent(Component comp)
{
	components.push_back(comp);
}

template <typename T>
T* GameObject::GetComponent()
{
	for (int i = 0; i < components.size(); i++)
	{
		//TODO
		//Check if any match using GetType, return
		if (components[i].GetType() == T::GetType())
			return components[i].GetComponent();
	}
}

void GameObject::Start()
{
	for (int i = 0; i < components.size(); i++)
	{
		components[i].Start();
	}
}

void GameObject::Update()
{
	for (int i = 0; i < components.size(); i++)
	{
		components[i].Update();
	}
}

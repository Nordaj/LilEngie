#include <iostream>
#include <string>
#include "GameObject.h"
#include "Component.h"

Component::Component(GameObject *obj)
	:obj(obj)
{ 
	obj->AddComponent(this);
}

const GameObject* Component::GetObj()
{
	return obj;
}

void Component::SetObj(GameObject *o)
{
	if (obj == nullptr)
		obj = o;
}

std::string Component::GetType()
{
	std::cout << "GetType virtual method din work..." << std::endl;
	return "";
}

void* Component::Get() 
{ 
	std::cout << "GetComponent virtual method din work.." << std::endl;
	return nullptr; 
}

void Component::Start()
{ }

void Component::Update()
{ }

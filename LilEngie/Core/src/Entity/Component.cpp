#include <iostream>
#include <string>
#include <Application/Debug.h>
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
	LOG("GetType virtual method din work...", Warning, false);
	return "";
}

void* Component::Get() 
{ 
	LOG("GetComponent virtual method din work..", Warning, false);
	return nullptr; 
}

void Component::Start()
{ }

void Component::Update()
{ }

#include <iostream>
#include <string>
#include "GameObject.h"
#include "Component.h"

Component::Component(GameObject &obj)
	:obj(&obj)
{ }

const GameObject* Component::GetObj()
{
	return obj;
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

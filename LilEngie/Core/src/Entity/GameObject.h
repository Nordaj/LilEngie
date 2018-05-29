#pragma once

#include <vector>
#include <string>
#include "Component.h"

class GameObject
{
private:
	std::vector<Component*> components;

public:
	void AddComponent(Component &comp);
	void* GetComponent(std::string comp);

	void Start();
	void Update();
};

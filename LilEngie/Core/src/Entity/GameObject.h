#pragma once

#include <vector>
#include <string>
#include "Component.h"

class GameObject
{
private:
	//Each component needs unique static char[]
	//for type plus get type method
	std::vector<Component> components;

public:
	void AddComponent(Component comp);

	template <typename T>
	T* GetComponent();

	void Start();
	void Update();
};

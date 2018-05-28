#pragma once

#include <string>

class GameObject;

//Just a base class for specific components
class Component
{
private:
	const GameObject *obj;

public:
	Component(GameObject *obj);
	const GameObject* GetObj();

	virtual std::string GetType() { return ""; }

	virtual void* GetComponent() { return nullptr; }

	virtual void Start();
	virtual void Update();
};

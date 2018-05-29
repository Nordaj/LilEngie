#pragma once

#include <string>

class GameObject;

class Component
{
protected:
	const GameObject *obj;

public:
	Component(GameObject *obj);
	const GameObject* GetObj();

	virtual std::string GetType();
	virtual void* Get();

	virtual void Start() {}
	virtual void Update() {}
};

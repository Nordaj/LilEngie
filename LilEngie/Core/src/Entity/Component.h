#pragma once

#include <string>

class GameObject;

class Component
{
protected:
	GameObject *obj;

public:
	Component(GameObject *obj);
	const GameObject* GetObj();
	void SetObj(GameObject *o);

	virtual std::string GetType();
	virtual void* Get();

	virtual void Start();
	virtual void Update();
};

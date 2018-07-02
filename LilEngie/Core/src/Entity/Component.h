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

#define COMPONENT_ID(x) public: static std::string GetTypeStatic() { return x; } std::string GetType() { return GetTypeStatic(); } void* Get() { return this; }

#pragma once

#include <vector>
#include <string>
#include "Component.h"

class Scene;

class GameObject
{
private:
	std::vector<Component*> components;
	Scene *myScene;

public:
	GameObject(Scene *scene = nullptr);
	~GameObject();

	void AddComponent(void *comp);
	void* GetComponent(std::string comp);
	Scene* GetMyScene();

	void Start();
	void Update();
};

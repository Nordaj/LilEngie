#pragma once

#include <vector>
#include "GameObject.h"

class Scene
{
private:
	std::vector<GameObject*> objects;

public:
	Scene(std::vector<GameObject*> objs = std::vector<GameObject*>());

	void AddObject(GameObject &obj);
	void Start();
	void Update();
	void Close();
};

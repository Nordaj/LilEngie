#pragma once

#include <vector>
#include "GameObject.h"

namespace ObjectManager
{
	namespace
	{
		std::vector<GameObject> objects;
	}

	void AddObject(GameObject obj);
	void Start();
	void Update();
}

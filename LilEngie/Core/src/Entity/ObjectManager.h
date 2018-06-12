#pragma once

#include <vector>
#include "GameObject.h"
#include "Scene.h"

namespace ObjectManager
{
	namespace
	{
		Scene *scene;
	}

	void SetScene(Scene *s);
	void AddObjectToCurrent(GameObject &obj);
	void Start();
	void Update();
	bool CheckScene();
}

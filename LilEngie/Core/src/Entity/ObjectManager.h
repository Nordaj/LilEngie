#pragma once

#include <vector>
#include <Entity/Components/Camera.h>
#include "GameObject.h"
#include "Scene.h"

namespace ObjectManager
{
	namespace
	{
		Scene *scene;
	}

	void SetScene(Scene *s);
	Scene* GetCurrent();
	void SetCurrentCamera(Camera *cam);
	void Start();
	void Update();
	bool CheckScene();
}

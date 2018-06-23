#pragma once

#include <vector>
#include <Entity/Components/Camera.h>
#include "Scene.h"

namespace SceneManager
{
	void SetScene(Scene *s);
	Scene* GetCurrent();
	void SetCurrentCamera(Camera *cam);
	void Start();
	void Update();
	bool CheckScene();
}

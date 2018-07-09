#pragma once

#include <Entity/Scene.h>

namespace SceneLoader
{
	//Handles creation and loading of the scene
	void LoadScene(const char *path, Scene **inScene, bool setCurrent = true);
}

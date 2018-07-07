#pragma once

#include <Entity/Scene.h>

namespace SceneLoader
{
	//Returns true on success
	void LoadScene(const char *path, Scene *scene);
}

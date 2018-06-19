#pragma once

#include <Entity/Scene.h>

namespace SceneLoader
{
	//Returns true on success
	bool LoadScene(const char *path, Scene *scene);
}

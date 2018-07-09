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
	void UnloadScene(Scene **s);
	//Just an abstraction of SceneLoader::LoadScene
	void LoadScene(const char *path, Scene **inScene, bool setCurrent = true);
	void Close();
}

namespace Scenes = SceneManager;

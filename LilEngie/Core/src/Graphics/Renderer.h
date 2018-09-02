#pragma once

#include <vector>
#include <Entity/Components/Mesh.h>
#include <Entity/Components/Camera.h>
#include <Entity/Scene.h>

namespace Renderer
{
	extern bool cullBackFaces;

	Camera* GetCurrentCamera();
	void SetScene(Scene *s);
	void SetClearColor(float r, float g, float b, float a);
	void Init();
	void Render();
	void Resize(int width, int height);
}

#pragma once

#include <vector>
#include <Entity/Components/Mesh.h>
#include <Entity/Components/Camera.h>

namespace Renderer
{
	namespace
	{
		std::vector<Mesh*> meshes;
		Camera *currentCamera;
		unsigned int defaultTex;
	}

	Camera* GetCurrentCamera();
	void SetClearColor(float r, float g, float b, float a);
	void SetCurrentCamera(Camera *cam);
	void AddMesh(Mesh &mesh);
	void Init();
	void Render();
}

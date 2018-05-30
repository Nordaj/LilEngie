#pragma once

#include <vector>
#include <Entity/Components/Mesh.h>

namespace Renderer
{
	namespace
	{
		std::vector<Mesh*> meshes;
	}

	void SetClearColor(float r, float g, float b, float a);
	void AddMesh(Mesh &mesh);
	void Init();
	void Render();
}

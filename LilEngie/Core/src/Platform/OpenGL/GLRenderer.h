#pragma once

#include "../Gfx.h"

namespace GLRenderer
{
	void SetClearColor(float r, float g, float b, float a);
	bool Init();
	void SetBlendingMode(Gfx::BlendFunction source, Gfx::BlendFunction destination);
	void DepthTest(bool mode);
	void Render();
	void Clear();
	void Blending(bool mode);
	void Viewport(int x, int y, int width, int height);
	void SubVertData(unsigned int vbo, int size, void *data);
	void Shutdown();
}

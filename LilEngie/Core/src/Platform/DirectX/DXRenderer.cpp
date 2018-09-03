#include <Application/Debug.h>
#include "../Gfx.h"
#include "DXRenderer.h"

namespace DXRenderer
{
	//Private
	unsigned int TranslateBlendingMode(Gfx::BlendFunction func);
}

void DXRenderer::SetClearColor(float r, float g, float b, float a)
{

}

bool DXRenderer::Init()
{
	return true;
}

void DXRenderer::SetBlendingMode(Gfx::BlendFunction source, Gfx::BlendFunction destination)
{

}

void DXRenderer::DepthTest(bool mode)
{

}

void DXRenderer::Clear()
{

}

void DXRenderer::Blending(bool mode)
{

}

void DXRenderer::Viewport(int x, int y, int width, int height)
{

}

void DXRenderer::SubVertData(unsigned int vbo, int size, void *data)
{

}

unsigned int DXRenderer::TranslateBlendingMode(Gfx::BlendFunction func)
{
	return 0;
}

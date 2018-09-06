#include <GL/glew.h>
#include <Application/Debug.h>
#include "../Gfx.h"
#include "GLRenderer.h"

namespace GLRenderer
{
	//Private
	unsigned int TranslateBlendingMode(Gfx::BlendFunction func);
}

void GLRenderer::SetClearColor(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
}

bool GLRenderer::Init()
{
	if (glewInit() != GLEW_OK)
		return false;

	return true;
}

void GLRenderer::SetBlendingMode(Gfx::BlendFunction source, Gfx::BlendFunction destination)
{
	unsigned int src = TranslateBlendingMode(source);
	unsigned int dst = TranslateBlendingMode(destination);
	glBlendFunc(src, dst);
}

void GLRenderer::DepthTest(bool mode)
{
	if (mode)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);
}

void GLRenderer::Render()
{

}

void GLRenderer::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLRenderer::Blending(bool mode)
{
	if (mode)
		glEnable(GL_BLEND);
	else
		glDisable(GL_BLEND);
}

void GLRenderer::Viewport(int x, int y, int width, int height)
{
	glViewport(x, y, width, height);
}

void GLRenderer::SubVertData(unsigned int vbo, int size, void *data)
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}

void GLRenderer::Shutdown()
{

}

unsigned int GLRenderer::TranslateBlendingMode(Gfx::BlendFunction func)
{
	switch (func)
	{
		case Gfx::BlendFunction::Zero:
			return GL_ZERO;
		case Gfx::BlendFunction::One:
			return GL_ONE;
		case Gfx::BlendFunction::SrcAlpha:
			return GL_SRC_ALPHA;
		case Gfx::BlendFunction::DestAlpha:
			return GL_DST_ALPHA;
		case Gfx::BlendFunction::OneMinusSrcAlpha:
			return GL_ONE_MINUS_SRC_ALPHA;
	}
}

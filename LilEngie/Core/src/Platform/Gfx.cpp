#include <vector>
#include <glm/glm.hpp>
#include <Graphics/Vertex.h>
#include "OpenGL/GLRenderer.h"
#include "OpenGL/GLUniformHandler.h"
#include "OpenGL/GLMeshRenderer.h"
#include "OpenGL/GLShaders.h"
#include "OpenGL/GLTexture.h"
#include "Gfx.h"

namespace Gfx
{
	//Public
	API api = API::OpenGL;
}

#pragma region Renderer
void Gfx::SetClearColor(float r, float g, float b, float a)
{
	if (api == API::OpenGL)
		GLRenderer::SetClearColor(r, g, b, a);
}

bool Gfx::InitRenderer()
{
	if (api == API::OpenGL)
		return GLRenderer::Init();
	return false;
}

void Gfx::SetBlendingMode(BlendFunction source, BlendFunction destination)
{
	if (api == API::OpenGL)
		GLRenderer::SetBlendingMode(source, destination);
}

void Gfx::DepthTest(bool mode)
{
	if (api == API::OpenGL)
		GLRenderer::DepthTest(mode);
}

void Gfx::ClearFrame()
{
	if (api == API::OpenGL)
		GLRenderer::Clear();
}

void Gfx::Blending(bool mode)
{
	if (api == API::OpenGL)
		GLRenderer::Blending(mode);
}

void Gfx::Viewport(int x, int y, int width, int height)
{
	if (api == API::OpenGL)
		GLRenderer::Viewport(x, y, width, height);
}

void Gfx::SubVertData(unsigned int vbo, int size, void *data)
{
	if (api == API::OpenGL)
		GLRenderer::SubVertData(vbo, size, data);
}
#pragma endregion Renderer

#pragma region UniformHandler
void Gfx::PassFloat(int shader, const char *name, float val)
{
	if (api == API::OpenGL)
		GLUniformHandler::PassFloat(shader, name, val);
}

void Gfx::PassInt(int shader, const char *name, int val)
{
	if (api == API::OpenGL)
		GLUniformHandler::PassInt(shader, name, val);
}

void Gfx::PassMat4(int shader, const char *name, glm::mat4 &val)
{
	if (api == API::OpenGL)
		GLUniformHandler::PassMat4(shader, name, val);
}

void Gfx::PassVec3(int shader, const char *name, glm::vec3 &val)
{
	if (api == API::OpenGL)
		GLUniformHandler::PassVec3(shader, name, val);
}

void Gfx::PassVec4(int shader, const char *name, glm::vec4 &val)
{
	if (api == API::OpenGL)
		GLUniformHandler::PassVec4(shader, name, val);
}
void Gfx::PassTexture(int shader, const char* name, unsigned int texUnit, unsigned int texture)
{
	if (api == API::OpenGL)
		GLUniformHandler::PassTexture(shader, name, texUnit, texture);
}
#pragma endregion UniformHandler

#pragma region MeshRenderer
void Gfx::SetupMesh(std::vector<Vertex> &v, std::vector<unsigned int> &i, unsigned int *vao, unsigned int *vbo, unsigned int *ibo)
{
	if (api == API::OpenGL)
		GLMeshRenderer::Setup(v, i, vao, vbo, ibo);
}

void Gfx::SetupPosUVMesh(std::vector<float> &v, std::vector<unsigned int> &i, unsigned int *vao, unsigned int *vbo, unsigned int *ibo)
{
	if (api == API::OpenGL)
		GLMeshRenderer::SetupPosUV(v, i, vao, vbo, ibo);
}

void Gfx::DrawMesh(unsigned int vao, unsigned int indicesSize)
{
	if (api == API::OpenGL)
		GLMeshRenderer::Draw(vao, indicesSize);
}
#pragma endregion MeshRenderer

#pragma region Shaders
void Gfx::UseShader(unsigned int shaderID)
{
	if (api == API::OpenGL)
		GLShaders::Use(shaderID);
}

unsigned int Gfx::SetupShader(const char *vert, const char *surf)
{
	if (api == API::OpenGL)
		return GLShaders::SetupShader(vert, surf);
}
#pragma endregion Shaders

#pragma region Texture
unsigned int Gfx::CreateTexture(int channels, int width, int height, unsigned char *data, bool repeat, bool filter)
{
	if (api == API::OpenGL)
		return GLTexture::Create(channels, width, height, data, repeat, filter);
}

void Gfx::CreateDefaultTex(unsigned int *tex)
{
	if (api == API::OpenGL)
		GLTexture::CreateDefaultTex(tex);
}

void Gfx::BindTexture(unsigned int tex, unsigned int slot)
{
	if (api == API::OpenGL)
		GLTexture::BindTexture(tex, slot);
}
#pragma endregion Texture

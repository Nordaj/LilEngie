#pragma once

#include <vector>
#include <glm/glm.hpp>
class Vertex;

namespace Gfx
{
	enum API : char { DirectX, OpenGL };
	extern API api;

	//Renderer
	enum BlendFunction { Zero, One, SrcAlpha, DestAlpha, OneMinusSrcAlpha };
	void SetClearColor(float r, float g, float b, float a);
	bool InitRenderer();
	void SetBlendingMode(BlendFunction source, BlendFunction destination);
	void DepthTest(bool mode);
	void Render();
	void Clear();
	void Blending(bool mode);
	void Viewport(int x, int y, int width, int height);
	void SubVertData(unsigned int vbo, int size, void *data);
	void Shutdown();

	//UniformHandler
	void PassFloat(int shader, const char *name, float val);
	void PassInt(int shader, const char *name, int val);
	void PassMat4(int shader, const char *name, glm::mat4 &val);
	void PassVec3(int shader, const char *name, glm::vec3 &val);
	void PassVec4(int shader, const char *name, glm::vec4 &val);
	void PassTexture(int shader, const char* name, unsigned int texUnit, unsigned int texture);

	//MeshRenderer
	void SetupMesh(std::vector<Vertex> &v, std::vector<unsigned int> &i, unsigned int *vao, unsigned int *vbo, unsigned int *ibo);
	void SetupPosUVMesh(std::vector<float> &v, std::vector<unsigned int> &i, unsigned int *vao, unsigned int *vbo, unsigned int *ibo);
	void DrawMesh(unsigned int vao, unsigned int indicesSize);

	//Shaders
	void UseShader(unsigned int shaderID);
	unsigned int SetupShader(const char *vert, const char *surf);

	//Texture
	unsigned int CreateTexture(int channels, int width, int height, unsigned char *data, bool repeat, bool filter);
	void CreateDefaultTex(unsigned int *tex);
	void BindTexture(unsigned int tex, unsigned int slot);

	//Use typedefs that have void pointers as a general memory thing but to also be nice and specific across platforms
}

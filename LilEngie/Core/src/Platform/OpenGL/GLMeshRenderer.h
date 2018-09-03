#pragma once

#include <vector>
class Vertex;

namespace GLMeshRenderer
{
	void Setup(std::vector<Vertex> &v, std::vector<unsigned int> &i, unsigned int *vao, unsigned int *vbo, unsigned int *ibo);
	void SetupPosUV(std::vector<float> &v, std::vector<unsigned int> &i, unsigned int *vao, unsigned int *vbo, unsigned int *ibo);
	void Draw(unsigned int vao, unsigned int indicesSize);
}

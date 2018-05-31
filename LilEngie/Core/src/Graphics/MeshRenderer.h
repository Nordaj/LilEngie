#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>

#include "Shader.h"

class MeshRenderer
{
private:
	std::vector<float> vertices;
	std::vector<unsigned int> indices;

	Shader shader;
	unsigned int VBO;
	unsigned int IBO;
	unsigned int VAO;

public:
	MeshRenderer() {}

	void Setup(std::vector<float> v, std::vector<unsigned int> i, std::string &path);
	void Draw(glm::mat4 &MVP);
};

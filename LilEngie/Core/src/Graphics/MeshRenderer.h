#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>

#include "Material.h"

class MeshRenderer
{
private:
	std::vector<float> vertices;
	std::vector<unsigned int> indices;

	Material *material;
	unsigned int VBO;
	unsigned int IBO;
	unsigned int VAO;

public:
	MeshRenderer() {}

	void Setup(std::vector<float> v, std::vector<unsigned int> i, Material *mat);
	void Draw(glm::mat4 &MVP);
};

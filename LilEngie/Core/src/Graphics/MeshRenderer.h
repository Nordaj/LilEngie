#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>

#include "Model.h"
#include "Material.h"

class MeshRenderer
{
private:
	Model model;

	int material;
	unsigned int VBO;
	unsigned int IBO;
	unsigned int VAO;

public:
	MeshRenderer() {}

	void Setup(std::vector<float> v, std::vector<unsigned int> i, int mat);
	void Draw(glm::mat4 &MVP, glm::mat4 &model);
};

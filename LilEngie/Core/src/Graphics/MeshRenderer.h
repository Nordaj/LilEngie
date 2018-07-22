#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include "Model.h"
#include "Vertex.h"
#include "Material.h"

class MeshRenderer
{
private:
	Model model;
	Material *material;

	unsigned int VBO;
	unsigned int IBO;
	unsigned int VAO;

public:
	MeshRenderer() {}

	void Setup(std::vector<Vertex> &v, std::vector<unsigned int> &i, Material *mat);
	void Draw(glm::mat4 &MVP, glm::mat4 &model, glm::vec3 &camPos);
	void Draw();
};

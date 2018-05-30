#pragma once

#include <vector>
#include <glm/glm.hpp>

class MeshRenderer
{
private:
	std::vector<float> vertices;
	std::vector<unsigned int> indices;

	unsigned int shader;
	unsigned int VBO;
	unsigned int IBO;
	unsigned int VAO;

public:
	MeshRenderer() {}

	void Setup(std::vector<float> v, std::vector<unsigned int> i, unsigned int s);
	void Draw(glm::mat4 &MVP);
};

#pragma once

#include <string>
#include <glm/glm.hpp>
#include <Graphics/Model.h>
#include <Graphics/Material.h>

class TextRenderer
{
private:
	unsigned int VBO;
	unsigned int IBO;
	unsigned int VAO;

public:
	TextRenderer();

	float scale;
	glm::vec2 position;
	glm::vec3 color;
	std::string text;

	void Draw();
};

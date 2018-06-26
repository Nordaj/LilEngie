#pragma once

#include <string>
#include <glm/glm.hpp>
#include "Font.h"

//Text object that stores text, text data, and handles rendering
class TextRenderer
{
public:
	float size;
	glm::vec2 position;
	glm::vec3 color;
	std::string text;
	std::string fontName;

	void Render(Font *font);
};

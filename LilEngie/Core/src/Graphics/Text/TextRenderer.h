#pragma once

#include <string>
#include <glm/glm.hpp>
#include <Entity/Scene.h>
#include "Font.h"

//Text object that stores text, text data, and handles rendering
class TextRenderer
{
public:
	float size = 10;
	glm::vec2 position;
	glm::vec4 color;
	std::string text;
	std::string fontName;
	//Don't worry about assigning the font texture. I got you bro
	std::string materialName;
	Scene *scene;

	void Render(Font *font);

private:
	glm::vec2 ToPixelBased(glm::vec2 normalizedCoord);
	glm::vec2 ToNormalized(glm::vec2 pixelBasedCoord);
};

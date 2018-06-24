#pragma once

#include <glm/common.hpp>

class Character
{
public:
	unsigned int texID;
	glm::vec2 size;
	glm::vec2 bearing;
	float advance;
};

namespace TextRenderer
{
	void Init();
}

namespace Text = TextRenderer;

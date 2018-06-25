#pragma once

#include <glm/glm.hpp>
#include <Graphics/Texture.h>

class Character
{
public:
	Texture tex;
	int sizeX, sizeY;
	int bearingX, bearingY;
	float advance;

	Character() {}
	Character(Texture tex, int sizeX, int sizeY, int bearingX, int bearingY, float advance);
};

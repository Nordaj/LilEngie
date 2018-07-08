#pragma once

#include <unordered_map>
#include "Character.h"

//Holds all characters in hasmap for easy rendering
class Font
{
public:
	unsigned int texID;
	int width, height;
	float size;
	std::unordered_map<char, Character> characters;

	Font() {}
	~Font();
	void Clean();
	void SetupTexture(const char *path);
};

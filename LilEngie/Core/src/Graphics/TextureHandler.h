#pragma once

#include <unordered_map>
#include <string>
#include "Texture.h"

class TextureHandler
{
private:
	std::unordered_map<std::string, Texture> textures;

public:
	Texture *Get(std::string name);
	void AddTex(std::string name, Texture tex);
	void Clean();
};

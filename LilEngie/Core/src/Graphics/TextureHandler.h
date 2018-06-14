#pragma once

#include <unordered_map>
#include <string>
#include "Texture.h"

namespace TextureHandler
{
	namespace
	{
		std::unordered_map<std::string, Texture> textures;
	}

	Texture *Get(std::string name);
	void AddTex(std::string name, Texture tex);
}

namespace Textures = TextureHandler;

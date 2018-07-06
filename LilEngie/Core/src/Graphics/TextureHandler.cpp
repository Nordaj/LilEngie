#include <unordered_map>
#include <string>
#include "Texture.h"
#include "TextureHandler.h"

Texture *TextureHandler::Get(std::string name)
{
	return &textures[name];
}

void TextureHandler::AddTex(std::string name, Texture tex)
{
	textures.insert(std::make_pair(name, tex));
}

void TextureHandler::Clean()
{
	textures.clear();
}

#include <unordered_map>
#include <glm/common.hpp>
#include <ft2build.h>
#include <freetype/freetype.h>
#include <Application/Debug.h>
#include "TextRenderer.h"

namespace TextRenderer
{
	//Private
	std::unordered_map<char, Character> characters;
	FT_Library ft;
	FT_Face face; //Later on support multiple
}

void TextRenderer::Init()
{
	//Init freetype
	if (FT_Init_FreeType(&ft) != 0)
		ERROR("Could not init freetype");

	//Setup default face
	if (FT_New_Face(ft, "Resources/Fonts/Standard/Monsterrat.ttf", 0, &face) != 0)
		ERROR("Could not load font");
	FT_Set_Pixel_Sizes(face, 0, 48);

	//TODO: finish this stuff
}

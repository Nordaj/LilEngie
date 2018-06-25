#include <unordered_map>
#include <GL/glew.h>
#include <glm/common.hpp>
#include <ft2build.h>
#include <freetype/freetype.h>
#include <Application/Debug.h>
#include "Character.h"
#include <Graphics/Texture.h>
#include "TextHandler.h"

namespace TextHandler
{
	//Private
	std::unordered_map<char, Character> characters;
}

void TextHandler::Init()
{
	FT_Library ft;
	FT_Face face;

	//Init freetype
	if (FT_Init_FreeType(&ft) != 0)
		ERROR("Could not init freetype");

	//Setup default face
	if (FT_New_Face(ft, "Resources/Fonts/Standard/Monsterrat.ttf", 0, &face) != 0)
		ERROR("Could not load font");
	FT_Set_Pixel_Sizes(face, 0, 48);

	//Disable 4 byte alignment
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	//Create texture for every ASCII character
	for (char c = 0; c < 128; c++)
	{
		//Load char glyph
		if (FT_Load_Char(face, c, FT_LOAD_RENDER) != 0)
			ERROR("Could not load char from font");

		//Setup texture
		Texture t = Texture(face->glyph->bitmap.buffer, face->glyph->bitmap.width, face->glyph->bitmap.rows);

		//Create character
		Character character = Character(
			t, 
			face->glyph->bitmap.width, 
			face->glyph->bitmap.rows,
			face->glyph->bitmap_left,
			face->glyph->bitmap_top,
			face->glyph->advance.x);

		//Insert it into hash map
		characters.insert(std::make_pair(c, character));
	}

	//Cleanup freetype
	FT_Done_Face(face);
	FT_Done_FreeType(ft);
}

Character *TextHandler::GetChar(char c)
{
	return &characters[c];
}

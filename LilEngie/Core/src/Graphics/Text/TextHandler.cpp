#include <string>
#include <unordered_map>
#include <vector>
#include "Font.h"
#include "TextRenderer.h"
#include "FontLoader.h"
#include "TextHandler.h"

namespace TextHandler
{
	//Private
	std::unordered_map<std::string, Font*> fonts;

	//Public
	std::vector<TextRenderer> texts = std::vector<TextRenderer>();
}

void TextHandler::Init()
{
	//Add default font
	AddFont("Ariel", "Resources/Fonts/Standard/Ariel.fnt");
}

void TextHandler::AddFont(const char *name, const char *path)
{
	Font *font = new Font();
	FontLoader::Load(path, &font->characters);
	//TODO: Figure out what to do about tex loading

	fonts.insert(std::make_pair(name, font));
}

void TextHandler::Render()
{
	for (int i = 0; i < texts.size(); i++)
	{
		Font *f = fonts[texts[i].fontName];
		texts[i].Render(f);
	}
}

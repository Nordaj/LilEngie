#include <string>
#include <map>
#include <vector>
#include <Platform/Gfx.h>
#include <Graphics/BaseMeshes.h>
#include "Font.h"
#include "TextRenderer.h"
#include "FontLoader.h"
#include "TextHandler.h"

//Initialize static stuff
unsigned int TextHandler::VBO = 0;
unsigned int TextHandler::IBO = 0;
unsigned int TextHandler::VAO = 0;

TextHandler::TextHandler()
{
	//Add default font
	AddFont("Ariel", "Resources/Fonts/Standard/Ariel.fnt");
}

TextHandler::~TextHandler()
{
	Clean();
}

void TextHandler::Init()
{
	//Setup characterMesh
	SetupCharQuad();
}

void TextHandler::AddFont(const char *name, const char *path)
{
	std::string texName;

	Font *font = new Font();
	FontLoader::Load(path, &(font->characters), &texName, &font->size);
	font->SetupTexture(texName.c_str());

	fonts.insert(std::make_pair(name, font));
}

void TextHandler::Render()
{
	for (int i = 0; i < texts.size(); i++)
	{
		Font *f = fonts[texts[i]->fontName];
		texts[i]->Render(f);
	}
}

void TextHandler::SetupCharQuad()
{
	Gfx::SetupPosUVMesh(BaseMeshes::charQuadVerts, BaseMeshes::charQuadInds, &VAO, &VBO, &IBO);
}

void TextHandler::Clean()
{
	//Free fonts memory
	std::map<std::string, Font*>::iterator it;
	for (it = fonts.begin(); it != fonts.end(); it++)
	{
		it->second->Clean();
		delete it->second;
	}

	//Clear fonts
	fonts.clear();

	//Clear texts
	texts.clear();
}

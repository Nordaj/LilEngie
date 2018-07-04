#include <string>
#include <unordered_map>
#include <vector>
#include <GL/glew.h>
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
	//Generate and bind VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//Generate vertex and index buffers
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);

	//Bind and give data to VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * BaseMeshes::charQuad.vertices.size(), &BaseMeshes::charQuad.vertices[0], GL_STATIC_DRAW);

	//Bind and give data to IBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * BaseMeshes::charQuad.indices.size(), &BaseMeshes::charQuad.indices[0], GL_STATIC_DRAW);

	//Vertex attributes (Position(v3), UV(v2))
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(sizeof(float) * 3));
}

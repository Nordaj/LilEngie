#pragma once

#include <vector>
#include "TextRenderer.h"
#include <Graphics/MeshRenderer.h>

//Takes care of all fonts, textrenderers, and loading
namespace TextHandler
{
	//Public
	extern std::vector<TextRenderer> texts;
	extern unsigned int VBO, IBO, VAO;

	void Init();
	void AddFont(const char *name, const char *font);
	void Render();
}

namespace Texts = TextHandler;

#pragma once

//Takes care of all fonts, textrenderers, and loading
namespace TextHandler
{
	//Public
	extern std::vector<TextRenderer> texts;

	void Init();
	void AddFont(const char *name, const char *font);
	void Render();
}

namespace Texts = TextHandler;

#pragma once

#include <vector>
#include <Graphics/MeshRenderer.h>

class Font;
class TextRenderer;

//Takes care of all fonts, textrenderers, and loading
class TextHandler
{
private:
	std::unordered_map<std::string, Font*> fonts;

public:
	std::vector<TextRenderer*> texts;
	static unsigned int VBO, IBO, VAO;

	TextHandler();
	void AddFont(const char *name, const char *font);
	void Render();

	static void Init();

private:
	static void SetupCharQuad();
};

#pragma once

#include <vector>
#include <map>
#include <Graphics/MeshRenderer.h>

class Font;
class TextRenderer;

//Takes care of all fonts, textrenderers, and loading
class TextHandler
{
private:
	std::map<std::string, Font*> fonts;

public:
	std::vector<TextRenderer*> texts;
	static unsigned int VBO, IBO, VAO;

	TextHandler();
	void AddFont(const char *name, const char *font);
	void Render();
	void Clean();

	static void Init();

private:
	static void SetupCharQuad();
};

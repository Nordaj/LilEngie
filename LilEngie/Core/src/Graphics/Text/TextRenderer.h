#pragma once

#include <string>
#include <glm/glm.hpp>
#include <Entity/Scene.h>
#include "Font.h"

//Text object that stores text, text data, and handles rendering
class TextRenderer
{
public:
	float size = 50;
	//Use 0-1 scale
	glm::vec2 position = { -1, 1 };
	glm::vec4 color = { 1, 1, 1, 1 };
	std::string text = "Sample Text";
	std::string fontName = "Ariel";
	//Don't worry about assigning the font texture. I got you bro
	std::string materialName;
	Scene *scene;

	void Render(Font *font);

private:
	enum Axis { X, Y };

	void PrepRender(Font *font);
	float FntToScreen(float f, Axis axis, Font *font = nullptr);
	float ConvertFontSizes(float f, Font *font = nullptr);
	float PixelsToScreenCoords(float f, Axis axis);
};

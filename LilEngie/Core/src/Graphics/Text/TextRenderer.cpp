#include <string>
#include <glm/glm.hpp>
#include <Platform/Gfx.h>
#include <Graphics/BaseMeshes.h>
#include <Graphics/MaterialHandler.h>
#include <Graphics/UniformHandler.h>
#include <Graphics/BaseMeshes.h>
#include <Application/Window.h>
#include "TextHandler.h"
#include "Font.h"
#include "TextRenderer.h"

//I just got annoyed by needing to cast so much shit
#define F(a) (float)a

void TextRenderer::Render(Font *font)
{
	float cursor = position.x;

	//Iterate through each character to render
	for (int i = 0; i < text.size(); i++)
	{
		//Prepare to render
		PrepRender(font);

		//Get character pointer for easy access
		Character *c = &font->characters[text[i]];

		//Calculate rect for UV's
		glm::vec4 uRect =
		{ //X, Y, Width, Height
				c->posX   / F(font->width),
			1 - c->posY   / F(font->height),
				c->width  / F(font->width),
				c->height / F(font->height)
		};

		//Calculate rect for positions
		glm::vec4 pRect = 
		{ //X, Y, Width, Height
			cursor	   + FntToScreen(c->offsetX, Axis::X, font),
			position.y - FntToScreen(c->offsetY, Axis::Y, font),
			FntToScreen(c->width,  Axis::X, font),
			FntToScreen(c->height, Axis::Y, font)
		};

		//Move cursor
		cursor += FntToScreen(c->advance, Axis::X, font);

		//Get new verts I want to replace VBO with
		float newVerts[] =
		{
			//Positions									     //Tex coords
			pRect[0]		   , pRect[1] - pRect[3], -0.5f, uRect[0],			  uRect[1] - uRect[3],	//0 (left bottom)
			pRect[0] + pRect[2], pRect[1] - pRect[3], -0.5f, uRect[0] + uRect[2], uRect[1] - uRect[3],	//1 (right bottom)
			pRect[0] + pRect[2], pRect[1]			, -0.5f, uRect[0] + uRect[2], uRect[1],				//2 (right top)
			pRect[0]		   , pRect[1]			, -0.5f, uRect[0],			  uRect[1],				//3 (left top)
		};

		//Submit new data
		Gfx::SubVertData(TextHandler::VBO, sizeof(newVerts), &newVerts[0]);

		//Draw the mesh
		Gfx::DrawMesh(TextHandler::VAO, BaseMeshes::charQuadInds.size());
	}

	Gfx::DepthTest(true);
}

void TextRenderer::PrepRender(Font *font)
{
	//Bind texture
	int t = font->texID;
	int s = scene->materials.Get(materialName)->GetShader()->GetID();
	UniformHandler::PassTexture(s, "uCharacters", 0, t);

	//Prep material
	scene->materials.Get(materialName)->Prepare();

	//Pass color data
	UniformHandler::PassVec4(s, "uColor", color);
}

//Take in float from font file. Convert it to a usable screen coordinate
float TextRenderer::FntToScreen(float f, Axis axis, Font *font)
{
	float r;
	r = ConvertFontSizes(f, font);
	r = PixelsToScreenCoords(r, axis);
	return r;
}

//Take in a float read from font file. Use font size of font texture & my font size to convert it
float TextRenderer::ConvertFontSizes(float f, Font *font)
{
	if (font == nullptr) //Assume size = 82.0f
		return (f / font->size) * size;
	//else //Use ref font size from font
	//TODO
}

//Take in a float representing pixels and convert it to 0-1 scale
float TextRenderer::PixelsToScreenCoords(float f, Axis axis)
{
	if (axis == X)
		return f / Window::width;
	else
		return f / Window::height;
}

//Cleanup like a good boy
#undef F

#include <string>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <Graphics/BaseMeshes.h>
#include <Graphics/MaterialHandler.h>
#include <Graphics/UniformHandler.h>
#include <Graphics/BaseMeshes.h>
#include <Application/Window.h>
#include "TextHandler.h"
#include "Font.h"
#include "TextRenderer.h"

void TextRenderer::Render(Font *font)
{
	for (int i = 0; i < text.size(); i++)
	{
		//Get character pointer for easy access
		Character *c = &font->characters[text[i]];

		//Bind texture
		int t = font->texID;
		int s = scene->materials.Get(materialName)->GetShader()->GetID();
		UniformHandler::PassTexture(s, "uCharacters", 0, t);

		//Prep material
		scene->materials.Get(materialName)->Prepare();

		//Pass color data
		UniformHandler::PassVec4(s, "uColor", color);

		//Convert tex coords from pixels to 0-1
		float posX = c->posX		/	(float)font->width;
		float posY = 1 - (c->posY	/	(float)font->height);
		float wdth = c->width		/	(float)font->width;
		float hght = c->height		/	(float)font->height;

		//Get new verts I want to replace VBO with
		float newVerts[] = 
		{
			//Positions          //Tex coord
			-0.5f, -0.5f, -0.5f, posX		, posY - hght, //0 (bottom 	left)
			 0.5f, -0.5f, -0.5f, posX + wdth, posY - hght, //1 (bottom 	right)
			 0.5f,  0.5f, -0.5f, posX + wdth, posY		 , //2 (top		right)
			-0.5f,  0.5f, -0.5f, posX		, posY		 , //3 (top		left)
		};

		//Submit new data
		glBindBuffer(GL_ARRAY_BUFFER, TextHandler::VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(newVerts), &newVerts[0]);

		//Bind VAO
		glBindVertexArray(TextHandler::VAO);

		//Draw
		glDrawElements(GL_TRIANGLES, BaseMeshes::charQuad.indices.size(), GL_UNSIGNED_INT, nullptr);
	}

	glEnable(GL_DEPTH_TEST);
}

glm::vec2 TextRenderer::ToPixelBased(glm::vec2 normalizedCoord)
{
	return glm::vec2(
		Window::width * normalizedCoord.x, 
		Window::height * normalizedCoord.y);
}

glm::vec2 TextRenderer::ToNormalized(glm::vec2 pixelBasedCoord)
{
	return glm::vec2(
		pixelBasedCoord.x / Window::width, 
		pixelBasedCoord.y / Window::height);
}

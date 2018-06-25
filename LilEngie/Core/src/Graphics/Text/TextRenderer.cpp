#include <GL/glew.h>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Graphics/Model.h>
#include <Graphics/Material.h>
#include <Graphics/UniformHandler.h>
#include <Graphics/BaseMeshes.h>
#include "TextHandler.h"
#include "Character.h"
#include "TextRenderer.h"

TextRenderer::TextRenderer()
{
	//Generate and bind VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//Generate vertex and index buffers
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);

	//Bind and give data to VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * BaseMeshes::quad.vertices.size(), &BaseMeshes::quad.vertices[0], GL_STATIC_DRAW);

	//Bind and give data to IBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * BaseMeshes::quad.indices.size(), &BaseMeshes::quad.indices[0], GL_STATIC_DRAW);

	//Vertex attributes (Position(v3), Normal(v3), UV(v2))
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 3));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 6));
}

void TextRenderer::Draw()
{
	//Somehow draw the series of characters
	for (int i = 0; i < text.size(); i++)
	{
		//Get character
		Character *c = TextHandler::GetChar(text[i]);

		//Dude i dont even know yet
	}
}

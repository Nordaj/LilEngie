#include <GL/glew.h>
#include <iostream>

#include "UniformHandler.h"
#include "Renderer.h"
#include "MeshRenderer.h"

void MeshRenderer::Setup(std::vector<float> v, std::vector<unsigned int> i, unsigned int s)
{
	//Assign values
	vertices = v;
	indices = i;
	shader = s;

	//Generate and bind VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//Generate vertex and index buffers
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);

	//Bind and give data to VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	//Bind and give data to IBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);

	//Vertex attributes (currently just positions)
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
}

void MeshRenderer::Draw(glm::mat4 &MVP)
{
	//Pass in mvp (not sure how i want to handle uniform names)
	//UniformHandler::PassMat4(shader, (char*)"uMVPMat", MVP);

	//Bind VAO
	glBindVertexArray(VAO);

	//Draw
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
}

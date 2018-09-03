#include <vector>
#include <GL/glew.h>
#include <Graphics/Vertex.h>
#include "GLMeshRenderer.h"

void GLMeshRenderer::Setup(std::vector<Vertex> &v, std::vector<unsigned int> &i, unsigned int *vao, unsigned int *vbo, unsigned int *ibo)
{
	//Generate and bind VAO
	glGenVertexArrays(1, vao);
	glBindVertexArray(*vao);

	//Generate vertex and index buffers
	glGenBuffers(1, vbo);
	glGenBuffers(1, ibo);

	//Bind and give data to VBO
	glBindBuffer(GL_ARRAY_BUFFER, *vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * v.size(), &v[0], GL_STATIC_DRAW);

	//Bind and give data to IBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * i.size(), &i[0], GL_STATIC_DRAW);

	//Vertex attributes (Position(v3), UV(v2), Normal(v3), Tangent(v3))
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 11, 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 11, (void*)(sizeof(float) * 3));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 11, (void*)(sizeof(float) * 5));

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 11, (void*)(sizeof(float) * 8));
}

void GLMeshRenderer::SetupPosUV(std::vector<float> &v, std::vector<unsigned int> &i, unsigned int *vao, unsigned int *vbo, unsigned int *ibo)
{
	//Generate and bind VAO
	glGenVertexArrays(1, vao);
	glBindVertexArray(*vao);

	//Generate vertex and index buffers
	glGenBuffers(1, vbo);
	glGenBuffers(1, ibo);

	//Bind and give data to VBO
	glBindBuffer(GL_ARRAY_BUFFER, *vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * v.size(), &v[0], GL_STATIC_DRAW);

	//Bind and give data to IBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * i.size(), &i[0], GL_STATIC_DRAW);

	//Vertex attributes (Position(v3), UV(v2))
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(sizeof(float) * 3));
}

void GLMeshRenderer::Draw(unsigned int vao, unsigned int indicesSize)
{
	//Bind VAO
	glBindVertexArray(vao);

	//Draw
	glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, nullptr);
}

#include <GL/glew.h>
#include <string>
#include <iostream>

#include "ShaderReader.h"
#include "UniformHandler.h"
#include "Renderer.h"
#include "MeshRenderer.h"

void MeshRenderer::Setup(std::vector<float> v, std::vector<unsigned int> i, std::string &path)
{
	std::string vert = "";
	std::string surf = "";
	ShaderReader::ReadShader(&vert, &surf, path);

	//Setup shader
	shader.Setup(vert, surf);

	//Assign values
	vertices = v;
	indices = i;

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
	//Set current shader
	shader.SetCurrent();

	//Pass in mvp
	UniformHandler::PassMat4(shader.GetID(), (char*)"uMVPMat", MVP);

	//Bind VAO
	glBindVertexArray(VAO);

	//Draw
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
}

#include <GL/glew.h>
#include <string>
#include <iostream>
#include "LightHandler.h"
#include "MaterialHandler.h"
#include "ShaderReader.h"
#include "UniformHandler.h"
#include "Renderer.h"
#include "Shader.h"
#include "MeshRenderer.h"

void MeshRenderer::Setup(std::vector<float> v, std::vector<unsigned int> i, int mat)
{
	//Set material
	material = mat;

	//Assign values
	model.vertices = v;
	model.indices = i;

	//Generate and bind VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//Generate vertex and index buffers
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);

	//Bind and give data to VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * model.vertices.size(), &model.vertices[0], GL_STATIC_DRAW);

	//Bind and give data to IBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * model.indices.size(), &model.indices[0], GL_STATIC_DRAW);

	//Vertex attributes (Position(v3), Normal(v3)
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(sizeof(float) * 3));
}

void MeshRenderer::Draw(glm::mat4 &MVP, glm::mat4 &modelMat)
{
	//Set current shader
	MaterialHandler::Get(material)->Prepare(MVP, modelMat);

	//Setup lighting
	LightHandler::Prepare(MaterialHandler::Get(material)->GetShader());

	//Bind VAO
	glBindVertexArray(VAO);

	//Draw
	glDrawElements(GL_TRIANGLES, model.indices.size(), GL_UNSIGNED_INT, nullptr);
}

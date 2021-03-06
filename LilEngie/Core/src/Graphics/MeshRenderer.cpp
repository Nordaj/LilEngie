#include <GL/glew.h>
#include <string>
#include <iostream>
#include "LightHandler.h"
#include "MaterialHandler.h"
#include "ShaderReader.h"
#include "UniformHandler.h"
#include "Renderer.h"
#include "Shader.h"
#include "Vertex.h"
#include "MeshRenderer.h"

void MeshRenderer::Setup(std::vector<Vertex> &v, std::vector<unsigned int> &i, Material *mat)
{
	//Assign values
	material = mat;
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * v.size(), &model.vertices[0], GL_STATIC_DRAW);

	//Bind and give data to IBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * model.indices.size(), &model.indices[0], GL_STATIC_DRAW);

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

void MeshRenderer::Draw(glm::mat4 &MVP, glm::mat4 &modelMat, glm::vec3 &camPos)
{
	//Set current shader
	material->Prepare(MVP, modelMat);

	//Setup lighting
	LightHandler::Prepare(material->GetShader());

	//Pass campos
	UniformHandler::PassVec3(material->GetShader()->GetID(), "uCamPos", camPos);

	//Bind VAO
	glBindVertexArray(VAO);

	//Draw
	glDrawElements(GL_TRIANGLES, model.indices.size(), GL_UNSIGNED_INT, nullptr);
}

void MeshRenderer::Draw()
{
	//Set current shader
	material->Prepare();

	//Setup lighting
	LightHandler::Prepare(material->GetShader());

	//Bind VAO
	glBindVertexArray(VAO);

	//Draw
	glDrawElements(GL_TRIANGLES, model.indices.size(), GL_UNSIGNED_INT, nullptr);
}

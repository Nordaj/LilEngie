#include <string>
#include <iostream>
#include <Platform/Gfx.h>
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

	Gfx::SetupMesh(v, i, &VAO, &VBO, &IBO);
}

void MeshRenderer::Draw(glm::mat4 &MVP, glm::mat4 &modelMat, glm::vec3 &camPos)
{
	//Set current shader
	material->Prepare(MVP, modelMat);

	//Setup lighting
	LightHandler::Prepare(material->GetShader());

	//Pass camera position
	UniformHandler::PassVec3(material->GetShader()->GetID(), "uCamPos", camPos);

	Gfx::DrawMesh(VAO, model.indices.size());
}

void MeshRenderer::Draw()
{
	//Set current shader
	material->Prepare();

	//Setup lighting
	LightHandler::Prepare(material->GetShader());

	Gfx::DrawMesh(VAO, model.indices.size());
}

#include <iostream>
#include <vector>
#include <Entity/Components/PointLight.h>
#include "Shader.h"
#include "ShaderHandler.h"
#include "UniformHandler.h"
#include "LightHandler.h"

namespace LightHandler
{
	//Private
	std::vector<PointLight*> pointLights;
	std::vector<DirectionalLight*> dirLights;
	std::vector<SpotLight*> spotLights;
	glm::vec3 ambient;
}

void LightHandler::AddPointLight(PointLight *light)
{
	pointLights.push_back(light);
}

void LightHandler::AddDirLight(DirectionalLight *light)
{
	dirLights.push_back(light);
}

void LightHandler::AddSpotLight(SpotLight *light)
{
	spotLights.push_back(light);
}

void LightHandler::SetAmbient(glm::vec3 a)
{
	ambient = a;
}

void LightHandler::Prepare(Shader *shader)
{
	//Pass each point light
	for (int i = 0; i < pointLights.size(); i++)
	{
		std::string posStr = "uPointLights[" + std::to_string(i) + "].position";
		std::string colStr = "uPointLights[" + std::to_string(i) + "].color";
		std::string iStr = "uPointLights[" + std::to_string(i) + "].intensity";

		UniformHandler::PassVec3(shader->GetID(), (char*)posStr.c_str(), pointLights[i]->pos);
		UniformHandler::PassVec3(shader->GetID(), (char*)colStr.c_str(), pointLights[i]->color);
		UniformHandler::PassFloat(shader->GetID(), (char*)iStr.c_str(), pointLights[i]->intensity);
	}

	//Pass each dir light
	for (int i = 0; i < dirLights.size(); i++)
	{
		std::string dirStr = "uDirLights[" + std::to_string(i) + "].direction";
		std::string colStr = "uDirLights[" + std::to_string(i) + "].color";
		std::string iStr = "uDirLights[" + std::to_string(i) + "].intensity";

		UniformHandler::PassVec3(shader->GetID(), (char*)dirStr.c_str(), dirLights[i]->dir);
		UniformHandler::PassVec3(shader->GetID(), (char*)colStr.c_str(), dirLights[i]->color);
		UniformHandler::PassFloat(shader->GetID(), (char*)iStr.c_str(), dirLights[i]->intensity);
	}

	//Pass each spot light
	for (int i = 0; i < spotLights.size(); i++)
	{
		std::string posStr = "uSpotLights[" + std::to_string(i) + "].position";
		std::string dirStr = "uSpotLights[" + std::to_string(i) + "].direction";
		std::string colStr = "uSpotLights[" + std::to_string(i) + "].color";
		std::string iStr = "uSpotLights[" + std::to_string(i) + "].intensity";
		std::string angStr = "uSpotLights[" + std::to_string(i) + "].angle";

		UniformHandler::PassVec3(shader->GetID(), (char*)posStr.c_str(), spotLights[i]->pos);
		UniformHandler::PassVec3(shader->GetID(), (char*)dirStr.c_str(), spotLights[i]->dir);
		UniformHandler::PassVec3(shader->GetID(), (char*)colStr.c_str(), spotLights[i]->color);
		UniformHandler::PassFloat(shader->GetID(), (char*)iStr.c_str(), spotLights[i]->intensity);
		UniformHandler::PassFloat(shader->GetID(), (char*)angStr.c_str(), spotLights[i]->angle);
	}

	//Pass ambient
	UniformHandler::PassVec3(shader->GetID(), (char*)"uAmbient", ambient);
}

void LightHandler::Clean()
{
	pointLights.clear();
	dirLights.clear();
	spotLights.clear();
	ambient = glm::vec3(0, 0, 0);
}

#include <vector>
#include <Entity/Components/PointLight.h>
#include "Shader.h"
#include "ShaderHandler.h"
#include "UniformHandler.h"
#include "LightHandler.h"

void LightHandler::AddPointLight(PointLight *light)
{
	pointLights.push_back(light);
}

void LightHandler::AddDirLight(DirectionalLight *light)
{
	dirLights.push_back(light);
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
}

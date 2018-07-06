#include "ShaderHandler.h"
#include "Shader.h"
#include "Material.h"
#include "MaterialHandler.h"

MaterialHandler::~MaterialHandler()
{
	Clean();
}

void MaterialHandler::Add(std::string name, std::string shader, ShaderHandler *shaderHandler)
{
	Material *mat = new Material(shader, shaderHandler);
	materials.insert(std::make_pair(name, mat));
}

Material* MaterialHandler::Get(std::string mat)
{
	return materials[mat];
}

void MaterialHandler::Clean()
{
	//Dealocate all materials
	std::map<std::string, Material*>::iterator it;
	for (it = materials.begin(); it != materials.end(); it++)
		delete it->second;

	//Clear
	materials.clear();
}

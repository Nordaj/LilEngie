#include "ShaderHandler.h"
#include "Shader.h"
#include "Material.h"
#include "MaterialHandler.h"

void MaterialHandler::Add(std::string name, std::string shader)
{
	materials.insert(std::make_pair(name, Material(shader)));
}

Material* MaterialHandler::Get(std::string mat)
{
	std::unordered_map<std::string, Material> &m = materials;
	return &materials[mat];
}

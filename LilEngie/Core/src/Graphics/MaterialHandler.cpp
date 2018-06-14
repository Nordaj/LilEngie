#include "ShaderHandler.h"
#include "Shader.h"
#include "Material.h"
#include "MaterialHandler.h"

mat MaterialHandler::Create(std::string shader)
{
	materials.push_back(Material(shader));
	return materials.size() - 1;
}

Material* MaterialHandler::Get(mat index)
{
	return &materials[index];
}

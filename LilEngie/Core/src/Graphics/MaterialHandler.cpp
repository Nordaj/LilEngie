#include "Shader.h"
#include "Material.h"
#include "MaterialHandler.h"

int MaterialHandler::CreateMaterial(int shader)
{
	materials.push_back(Material(shader));
	return materials.size() - 1;
}

Material* MaterialHandler::GetMaterial(int index)
{
	return &materials[index];
}

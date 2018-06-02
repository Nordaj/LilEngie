#include "Shader.h"
#include "Material.h"
#include "MaterialHandler.h"

Material* MaterialHandler::CreateMaterial(Shader *shader)
{
	materials.push_back(Material(shader));
	return &(materials.back());
}

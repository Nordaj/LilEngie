#pragma once

#include <vector>
#include "Material.h"
#include "ShaderHandler.h"

//Just to be clear what it is when storing
typedef int mat;

namespace MaterialHandler
{
	namespace
	{
		std::vector<Material> materials;
	}

	mat Create(shader shader);
	Material* Get(mat index);
}

//Alternative name
namespace Mats = MaterialHandler;

#pragma once

#include <vector>
#include "Material.h"

namespace MaterialHandler
{
	namespace
	{
		std::vector<Material> materials;
	}

	Material* CreateMaterial(Shader *shader);
}

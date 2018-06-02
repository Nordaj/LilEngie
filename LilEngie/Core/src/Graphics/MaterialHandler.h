#pragma once

#include <vector>
#include "Material.h"

namespace MaterialHandler
{
	namespace
	{
		std::vector<Material> materials;
	}

	int CreateMaterial(int shader);
	Material* GetMaterial(int index);
}

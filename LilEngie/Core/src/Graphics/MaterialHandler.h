#pragma once

#include <unordered_map>
#include <string>
#include "Material.h"
#include "ShaderHandler.h"

namespace MaterialHandler
{
	namespace
	{
		std::unordered_map<std::string, Material> materials;
	}

	void Add(std::string name, std::string shader);
	Material* Get(std::string mat);
}

//Alternative name
namespace Mats = MaterialHandler;

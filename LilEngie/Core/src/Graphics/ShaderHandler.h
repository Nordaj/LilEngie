#pragma once

#include <string>
#include <unordered_map>

#include "Shader.h"

namespace ShaderHandler
{
	namespace
	{
		std::unordered_map<std::string, Shader> shaders;
	}

	void Create(std::string name, const char *path);
	Shader *Get(std::string name);
}

//Alternative name
namespace Shaders = ShaderHandler;

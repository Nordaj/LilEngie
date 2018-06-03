#pragma once

#include <vector>

#include "Shader.h"

//Just to be clear what it is when storing
typedef int shader;

namespace ShaderHandler
{
	namespace
	{
		std::vector<Shader> shaders;
	}

	shader Create(const char *path);
	Shader* Get(shader index);

	void SetShader(shader index);
}

//Alternative name
namespace Shaders = ShaderHandler;

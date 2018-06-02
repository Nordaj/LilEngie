#pragma once

#include <vector>

#include "Shader.h"

namespace ShaderHandler
{
	namespace
	{
		std::vector<Shader> shaders;
	}

	//Want to create easier to use functions that add automatically given path
	Shader* AddShader(const char *path);

	void SetShader(Shader *shader);
}

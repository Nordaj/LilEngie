#pragma once

#include <vector>

#include "Shader.h"

namespace ShaderHandler
{
	namespace
	{
		std::vector<Shader> shaders;
	}

	int AddShader(const char *path);
	Shader* GetShader(int index);

	void SetShader(int index);
}

#pragma once

#include <string>
#include <unordered_map>

#include "Shader.h"

class ShaderHandler
{
private:
	std::unordered_map<std::string, Shader> shaders;

public:
	void Create(std::string name, const char *path);
	Shader *Get(std::string name);

	//Would like to add get current method
};

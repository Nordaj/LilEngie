#pragma once

#include <map>
#include <string>
#include "Material.h"
#include "ShaderHandler.h"

class MaterialHandler
{
private:
	std::map<std::string, Material*> materials;

public:
	~MaterialHandler();
	void Add(std::string name, std::string shader, ShaderHandler *shaderHandler);
	Material* Get(std::string mat);
	void Clean();
};

#pragma once

#include <string>

class Shader
{
private:
	unsigned int shaderID;

public:
	Shader(unsigned int id);

	unsigned int GetID();
};

#pragma once

#include <string>

class Shader
{
private:
	unsigned int shaderID;

public:
	Shader() {}
	Shader(unsigned int id);

	unsigned int GetID();
	void Use();
};

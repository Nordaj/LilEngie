#pragma once

#include "Shader.h"
#include "ShaderHandler.h"

Shader::Shader(unsigned int id)
	:shaderID(id)
{ }

unsigned int Shader::GetID()
{
	return shaderID;
}

void Shader::SetCurrent()
{
	ShaderHandler::SetShader(this);
}

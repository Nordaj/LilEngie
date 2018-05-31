#pragma once

#include "Shader.h"
#include "ShaderHandler.h"

Shader::Shader()
{ }

unsigned int Shader::GetID()
{
	return shaderID;
}

void Shader::Setup(std::string vert, std::string surf)
{
	vertex = vert;
	surface = surf;

	shaderID = ShaderHandler::SetupShader(vert, surf);
}

void Shader::SetCurrent()
{
	ShaderHandler::SetShader(shaderID);
}

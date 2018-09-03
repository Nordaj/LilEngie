#include <iostream>
#include <vector>
#include <string>
#include <Platform/Gfx.h>

#include <Application/Debug.h>
#include "ShaderReader.h"
#include "Shader.h"
#include "ShaderHandler.h"

unsigned int SetupShader(std::string &vertex, std::string &surface)
{
	return Gfx::SetupShader(vertex.c_str(), surface.c_str());
}

void ShaderHandler::Create(std::string name, const char *path)
{
	//Read shader
	std::string vert, surf;
	ShaderReader::ReadShader(&vert, &surf, path);

	//Setup shader
	unsigned int id = SetupShader(vert, surf);

	//Create and add shader instance to list
	shaders.insert(std::make_pair(name, Shader(id)));
}

Shader *ShaderHandler::Get(std::string name)
{
	return &shaders[name];
}

void ShaderHandler::Clean()
{
	shaders.clear();
}

#include <vector>
#include <string>
#include <GL/glew.h>

#include "ShaderReader.h"
#include "Shader.h"
#include "ShaderHandler.h"

unsigned int CompileShader(std::string &src, int type)
{
	//Create shader
	unsigned int id = glCreateShader(type);

	//Give source
	const char *shader = src.c_str();
	glShaderSource(id, 1, &shader, nullptr);

	//Compile
	glCompileShader(id);

	return id;
}

unsigned int SetupShader(std::string &vertex, std::string &surface)
{
	//Create shader program
	unsigned int program = glCreateProgram();

	//Compile shaders
	unsigned int vert = CompileShader(vertex, GL_VERTEX_SHADER);
	unsigned int surf = CompileShader(surface, GL_FRAGMENT_SHADER);

	//Give to opengl
	glAttachShader(program, vert);
	glAttachShader(program, surf);
	glLinkProgram(program);
	glValidateProgram(program);

	//Cleanup
	glDeleteShader(vert);
	glDeleteShader(surf);

	return program;
}

int ShaderHandler::Create(const char *path)
{
	//Read shader
	std::string vert, surf;
	ShaderReader::ReadShader(&vert, &surf, path);

	//Setup shader
	unsigned int id = SetupShader(vert, surf);

	//Create and add shader instance to list
	shaders.push_back(Shader(id));

	return shaders.size() - 1;
}

Shader* ShaderHandler::Get(shader index)
{
	return &shaders[index];
}

void ShaderHandler::SetShader(shader index)
{
	glUseProgram(shaders[index].GetID());
}

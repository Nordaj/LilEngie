#include <iostream>
#include <vector>
#include <string>
#include <GL/glew.h>

#include <Application/Debug.h>
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

	//Error handling
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		//Get length
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

		//Get message
		char *msg = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, msg);

		//Output
		LOG("Your shader doesn't work...");
		LOG(msg, Log);
	}

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

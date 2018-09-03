#include <GL/glew.h>
#include <iostream>
#include <Application/Debug.h>
#include "GLShaders.h"

namespace GLShaders
{
	unsigned int CompileShader(const char *src, int type);
}

void GLShaders::Use(unsigned int shaderID)
{
	glUseProgram(shaderID);
}

unsigned int GLShaders::SetupShader(const char *vertex, const char *surface)
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

unsigned int GLShaders::CompileShader(const char *src, int type)
{
	//Create shader
	unsigned int id = glCreateShader(type);

	//Give source
	glShaderSource(id, 1, &src, nullptr);

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
		LOG("Oopsy woopsy your shader made a poopsy");
		LOG(msg, Log);
	}

	return id;
}

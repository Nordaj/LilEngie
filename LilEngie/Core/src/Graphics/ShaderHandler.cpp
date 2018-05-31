#include <GL/glew.h>

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

unsigned int ShaderHandler::SetupShader(std::string &vertex, std::string &surface)
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

void ShaderHandler::SetShader(unsigned int id)
{
	glUseProgram(id);
}

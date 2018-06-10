#include <GL/glew.h>
#include <glm/glm.hpp>
#include "UniformHandler.h"

void UniformHandler::PassFloat(int shader, const char *name, float val)
{
	int loc = glGetUniformLocation(shader, name);
	glUniform1f(loc, val);
}

void UniformHandler::PassInt(int shader, const char *name, int val)
{
	int loc = glGetUniformLocation(shader, name);
	glUniform1i(loc, val);
}

void UniformHandler::PassMat4(int shader, const char *name, glm::mat4 &val)
{
	int loc = glGetUniformLocation(shader, name);
	glUniformMatrix4fv(loc, 1, false, &val[0][0]);
}

void UniformHandler::PassVec3(int shader, const char *name, glm::vec3 &val)
{
	int loc = glGetUniformLocation(shader, name);
	glUniform3f(loc, val.x, val.y, val.z);
}

void UniformHandler::PassVec4(int shader, const char *name, glm::vec4 &val)
{
	int loc = glGetUniformLocation(shader, name);
	glUniform4f(loc, val.x, val.y, val.z, val.w);
}

void UniformHandler::PassTexture(int shader, const char* name, unsigned int texUnit, unsigned int texture)
{
	glActiveTexture(GL_TEXTURE0 + texUnit);
	glBindTexture(GL_TEXTURE_2D, texture);
	PassInt(shader, name, texUnit);
}

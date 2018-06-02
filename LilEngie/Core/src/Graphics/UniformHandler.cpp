#include <GL/glew.h>
#include <glm/glm.hpp>
#include "UniformHandler.h"

void UniformHandler::PassFloat(int shader, char* name, float val)
{
	int loc = glGetUniformLocation(shader, name);
	glUniform1f(loc, val);
}

void UniformHandler::PassInt(int shader, char* name, int val)
{
	int loc = glGetUniformLocation(shader, name);
	glUniform1i(loc, val);
}

void UniformHandler::PassMat4(int shader, char* name, glm::mat4 &val)
{
	int loc = glGetUniformLocation(shader, name);
	glUniformMatrix4fv(loc, 1, false, &val[0][0]);
}

void UniformHandler::PassVec4(int shader, char* name, glm::vec4 &val)
{
	int loc = glGetUniformLocation(shader, name);
	glUniform4f(loc, val.x, val.y, val.z, val.w);
}

void UniformHandler::PassTexture(unsigned int texUnit, unsigned int texture)
{
	glActiveTexture(texUnit);
	glBindTexture(GL_TEXTURE_2D, texture);
}

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

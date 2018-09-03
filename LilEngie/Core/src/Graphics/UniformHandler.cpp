#include <Platform/Gfx.h>
#include <glm/glm.hpp>
#include "UniformHandler.h"

void UniformHandler::PassFloat(int shader, const char *name, float val)
{
	Gfx::PassFloat(shader, name, val);
}

void UniformHandler::PassInt(int shader, const char *name, int val)
{
	Gfx::PassInt(shader, name, val);
}

void UniformHandler::PassMat4(int shader, const char *name, glm::mat4 &val)
{
	Gfx::PassMat4(shader, name, val);
}

void UniformHandler::PassVec3(int shader, const char *name, glm::vec3 &val)
{
	Gfx::PassVec3(shader, name, val);
}

void UniformHandler::PassVec4(int shader, const char *name, glm::vec4 &val)
{
	Gfx::PassVec4(shader, name, val);
}

void UniformHandler::PassTexture(int shader, const char* name, unsigned int texUnit, unsigned int texture)
{
	Gfx::PassTexture(shader, name, texUnit, texture);
}

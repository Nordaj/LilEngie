#pragma once

#include <glm/glm.hpp>

namespace UniformHandler
{
	void PassFloat(int shader, const char *name, float val);
	void PassInt(int shader, const char *name, int val);
	void PassMat4(int shader, const char *name, glm::mat4 &val);
	void PassVec3(int shader, const char *name, glm::vec3 &val);
	void PassVec4(int shader, const char *name, glm::vec4 &val);
	void PassTexture(int shader, const char *name, unsigned int texUnit, unsigned int texture);
}

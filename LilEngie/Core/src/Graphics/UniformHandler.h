#pragma once

#include <glm/glm.hpp>

namespace UniformHandler
{
	void PassFloat(int shader, char* name, float val);
	void PassInt(int shader, char* name, int val);
	void PassMat4(int shader, char* name, glm::mat4 &val);
}

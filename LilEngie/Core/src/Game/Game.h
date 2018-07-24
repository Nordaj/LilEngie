#pragma once

#include <GLFW/glfw3.h>

typedef void(*vFunction)();

namespace Game
{
	void Init(vFunction callback = nullptr);
	void Run(vFunction callback = nullptr);
	void Close();
}

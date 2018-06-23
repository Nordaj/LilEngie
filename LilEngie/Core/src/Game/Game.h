#pragma once

#include <GLFW/glfw3.h>

typedef void(*vFunction)();

namespace Game
{
	void Init();
	void Run(vFunction callback = nullptr);
	void Close();
}

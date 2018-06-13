#pragma once

#include <GLFW/glfw3.h>

typedef void(*vFunction)();

//I'd rather namespaces than singletons
namespace Game
{
	void Init();
	void Run(vFunction callback = nullptr);
	void Close();
}

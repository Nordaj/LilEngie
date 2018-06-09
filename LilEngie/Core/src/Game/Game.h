#pragma once

#include <GLFW/glfw3.h>

//I'd rather namespaces than singletons
namespace Game
{
	void Init();
	void Run();
	void Close();
}

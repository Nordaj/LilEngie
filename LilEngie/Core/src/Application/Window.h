#pragma once

#include <GLFW/glfw3.h>

namespace Window
{
	//Private members
	namespace
	{
		GLFWwindow *window;
	}

	static int width = 512;
	static int height = 512;
	static char title[] = "My Game";

	void Init();
	bool Open();
	void SwapBuffers();
	void PollEvents();
	void Close();
}

#pragma once

#include <GLFW/glfw3.h>

namespace Window
{
	//Private members
	namespace
	{
		GLFWwindow *window;
	}

	static int width = 1280;
	static int height = 720;
	static char title[] = "My Game";

	void Init();
	bool Open();
	void SwapBuffers();
	void PollEvents();
	void Close();
}

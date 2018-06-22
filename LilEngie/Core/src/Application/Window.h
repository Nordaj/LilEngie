#pragma once

#include <GLFW/glfw3.h>

namespace Window
{
	//Private members
	namespace
	{
		GLFWwindow *window;
	}

	extern int width;
	extern int height;
	extern char title[];

	void Init();
	bool Open();
	void SwapBuffers();
	void PollEvents();
	void Close();
	void Clean();
}

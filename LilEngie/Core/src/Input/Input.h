#pragma once

#include <GLFW/glfw3.h>
#include "Keys.h"

namespace Input
{
	namespace
	{
		GLFWwindow *win;
	}

	void Init(GLFWwindow *window);
	bool GetKey(Key key);
	//Would like to add GetKeyDown and GetKeyUp but not sure how
	//Definitely TODO later
}

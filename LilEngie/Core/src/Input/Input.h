#pragma once

#include <GLFW/glfw3.h>
#include <glm/common.hpp>
#include "Keys.h"

namespace Input
{
	enum MouseBtn { Left = GLFW_MOUSE_BUTTON_LEFT, Right = GLFW_MOUSE_BUTTON_RIGHT, Middle = GLFW_MOUSE_BUTTON_MIDDLE };

	void Init(GLFWwindow *window);
	bool GetKey(Key key);
	bool GetKeyUp(Key key);
	bool GetMouse(MouseBtn btn);
	glm::vec2 GetPointerPos();
	bool GetMouseUp(MouseBtn btn);
	void PrepInput();
	//Would like to add GetKeyDown and GetKeyUp but not sure how
	//Definitely TODO later
}

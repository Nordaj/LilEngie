#include <GLFW/glfw3.h>
#include <glm/common.hpp>
#include "Keys.h"
#include "Input.h"

GLFWwindow *win;

void Input::Init(GLFWwindow *window)
{
	win = window;
}

bool Input::GetKey(Key key)
{
	return glfwGetKey(win, key) == GLFW_PRESS;
}

bool Input::GetKeyUp(Key key)
{
	//TODO
	return false;
}

bool Input::GetMouse(MouseBtn btn)
{
	return glfwGetMouseButton(win, btn) == GLFW_PRESS;
}

glm::vec2 Input::GetPointerPos()
{
	double x, y;
	glfwGetCursorPos(win, &x, &y);
	return glm::vec2((float)x, (float)y);
}

bool Input::GetMouseUp(MouseBtn btn)
{
	//TODO
	return false;
}

void Input::PrepInput()
{
	//TODO
}

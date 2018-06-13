#include <GLFW/glfw3.h>
#include "Keys.h"
#include "Input.h"

void Input::Init(GLFWwindow *window)
{
	win = window;
}

bool Input::GetKey(Key key)
{
	return glfwGetKey(win, key) == GLFW_PRESS;
}

#pragma once

#include <GLFW/glfw3.h>
#include <glm/common.hpp>
#include "Keys.h"

namespace Input
{
	void Init();
	void Update();
	void KeyEvent(Event event, Key key);

	bool GetKey(Key key);
	bool GetKeyPress(Key key);
	bool GetKeyUp(Key key);
	glm::vec2 GetPointerPos();
	bool GetMouse(MouseBtn btn);
	bool GetMousePress(MouseBtn btn);
	bool GetMouseUp(MouseBtn btn);
}

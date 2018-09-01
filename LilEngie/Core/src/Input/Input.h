#pragma once

#include <glm/common.hpp>
#include "Keys.h"

namespace Input
{
	extern bool lockCursorMode;
	extern bool cursorVisibility;

	void Init();
	void Update();
	void KeyEvent(Event event, Key key);
	void MouseEvent(float xDelta, float yDelta);

	void ShowCursor(bool show);

	bool GetKey(Key key);
	bool GetKeyDown(Key key);
	bool GetKeyUp(Key key);
	bool GetMouse(MouseBtn btn);
	bool GetMouseDown(MouseBtn btn);
	bool GetMouseUp(MouseBtn btn);

	glm::vec2 GetCursor(bool pixels = true);
	glm::vec2 MouseDelta(bool pixels = true);
}

#pragma once

#include <glm/common.hpp>
#include "Keys.h"

//TODO: want to be able to lock cursor and sense mouse axis like that

namespace Input
{
	void Init();
	void Update();
	void KeyEvent(Event event, Key key);
	void CursorEvent(int xPos, int yPos);

	bool GetKey(Key key);
	bool GetKeyDown(Key key);
	bool GetKeyUp(Key key);
	bool GetMouse(MouseBtn btn);
	bool GetMouseDown(MouseBtn btn);
	bool GetMouseUp(MouseBtn btn);
	glm::vec2 GetCursor(bool pixels = true);
	glm::vec2 GetMouseAxis(bool pixels = false);
}

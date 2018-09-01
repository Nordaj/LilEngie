#pragma once

#include <Input/Keys.h>
#include <basetsd.h>

namespace WinInput
{
	typedef void(*KeyEventCallback)(Input::Event, Input::Key);
	typedef void(*MouseMoveCallback)(float, float);

	void Init(KeyEventCallback keyEvCallback, MouseMoveCallback mouseMove);
	void KeyCallback(unsigned int msg, LONG_PTR wParam, UINT_PTR lParam);
	void MouseMove(float xDelta, float yDelta);
	void SetCursor(int xPos, int yPos);
	void GetCursor(int *xPos, int *yPos);
	void CursorVisibility(bool show);
}

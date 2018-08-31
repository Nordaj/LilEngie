#pragma once

#include <Input/Keys.h>
#include <basetsd.h>

namespace WinInput
{
	typedef void(*KeyEventCallback)(Input::Event, Input::Key);
	typedef void(*MouseMoveCallback)(int, int);

	void Init(KeyEventCallback keyEvCallback, MouseMoveCallback mouseMove);
	void KeyCallback(unsigned int msg, LONG_PTR wParam, UINT_PTR lParam);
	void MouseMove(int xPos, int yPos);
}

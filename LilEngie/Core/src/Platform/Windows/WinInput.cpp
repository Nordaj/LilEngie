#include <Input/Keys.h>
#include <Application/Window.h>
#include <Application/Debug.h>
#include "WinInput.h"

#include <Windows.h>

namespace WinInput
{
	//Private callback
	KeyEventCallback callback;
	MouseMoveCallback mouseCallback;
}

void WinInput::Init(KeyEventCallback keyEvCallback, MouseMoveCallback mouseMove)
{
	callback = keyEvCallback;
	mouseCallback = mouseMove;
}

void WinInput::KeyCallback(unsigned int msg, LONG_PTR wParam, UINT_PTR lParam)
{
	using namespace Input;

	switch (msg)
	{
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
			callback(Event::Down, (Key)wParam);
			break;
		case WM_KEYUP:
		case WM_SYSKEYUP:
			callback(Event::Release, (Key)wParam);
			break;
		case WM_LBUTTONDOWN:
			callback(Event::Down, Key::LeftMouseBtn);
			break;
		case WM_MBUTTONDOWN:
			callback(Event::Down, Key::MidMouseBtn);
			break;
		case WM_RBUTTONDOWN:
			callback(Event::Down, Key::RightMouseBtn);
			break;
		case WM_XBUTTONDOWN:
			if (HIWORD(wParam) == 1)
				callback(Event::Down, Key::ThumbBack);
			else
				callback(Event::Down, Key::ThumbForward);
			break;
		case WM_LBUTTONUP:
			callback(Event::Release, Key::LeftMouseBtn);
			break;
		case WM_MBUTTONUP:
			callback(Event::Release, Key::MidMouseBtn);
			break;
		case WM_RBUTTONUP:
			callback(Event::Release, Key::RightMouseBtn);
			break;
		case WM_XBUTTONUP:
			if (HIWORD(wParam) == 1)
				callback(Event::Release, Key::ThumbBack);
			else
				callback(Event::Release, Key::ThumbForward);
			break;
	}
}

void WinInput::MouseMove(int xPos, int yPos)
{
	mouseCallback(xPos, yPos);
}

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

	//Setup mouse input
	RAWINPUTDEVICE rid[1];
	rid[0].usUsagePage = 0x01;
	rid[0].usUsage = 0x02;
	rid[0].dwFlags = 0;
	rid[0].hwndTarget = 0;
	if (!RegisterRawInputDevices(rid, 1, sizeof(rid[0])))
		Debug::Log("Could not register mouse device");
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
		case WM_INPUT:
			UINT dwSize;
			GetRawInputData((HRAWINPUT)lParam, RID_INPUT, NULL, &dwSize, sizeof(RAWINPUTHEADER));
			LPBYTE lpb = new BYTE[dwSize];
			GetRawInputData((HRAWINPUT)lParam, RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER));
			RAWINPUT *raw = (RAWINPUT*)lpb;
			if (raw->header.dwType == RIM_TYPEMOUSE)
				MouseMove(raw->data.mouse.lLastX, raw->data.mouse.lLastY);
			delete[] lpb;
			break;
	}
}

void WinInput::MouseMove(float xDelta, float yDelta)
{
	mouseCallback(xDelta, yDelta);
}

void WinInput::SetCursor(int xPos, int yPos)
{
	SetCursorPos(xPos, yPos);
}

void WinInput::GetCursor(int *xPos, int *yPos)
{
	POINT p;
	GetCursorPos(&p);
	*xPos = p.x;
	*yPos = p.y;
}

void WinInput::CursorVisibility(bool show)
{
	ShowCursor(show);
}

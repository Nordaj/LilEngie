#include <unordered_map>
#include <string>
#include <glm/common.hpp>
#include <Application/Debug.h>
#include <Application/Window.h>
#include <Platform/Windows/WinInput.h>
#include "Keys.h"
#include "Input.h"

#define KEY_COUNT 255

namespace Input
{
	//Public
	bool lockCursorMode = false;
	bool cursorVisibility = true;

	//Private
	bool currentKeys[KEY_COUNT];
	bool pastKeys[KEY_COUNT];
	float mouseDeltaX, mouseDeltaY;
}

void Input::Init()
{
	WinInput::Init(KeyEvent, Input::MouseEvent);
}

void Input::Update()
{
	memcpy(&pastKeys[0], &currentKeys[0], KEY_COUNT);

	mouseDeltaX = 0;
	mouseDeltaY = 0;

	if (lockCursorMode)
	{
		int x, y;
		Window::GetWinPos(&x, &y);

		WinInput::SetCursor(x + (Window::width / 2), y + (Window::height / 2));
	}
}

void Input::KeyEvent(Event event, Key key)
{
	currentKeys[(int)key] = (bool)event;
}

void Input::MouseEvent(float xDelta, float yDelta)
{
	mouseDeltaX = xDelta;
	mouseDeltaY = yDelta;
}

bool Input::GetKey(Key key)
{
	return currentKeys[(int)key];
}

bool Input::GetKeyDown(Key key)
{
	if (!pastKeys[(int)key])
		return currentKeys[(int)key];
	else return false;
}

bool Input::GetKeyUp(Key key)
{
	if (pastKeys[(int)key])
		return !currentKeys[(int)key];
	else return false;
}

bool Input::GetMouse(MouseBtn btn)
{
	return GetKey((Key)btn);
}

bool Input::GetMouseDown(MouseBtn btn)
{
	return GetKeyDown((Key)btn);
}

bool Input::GetMouseUp(MouseBtn btn)
{
	return GetKeyUp((Key)btn);
}

glm::vec2 Input::GetCursor(bool pixels)
{
	int x, y;
	WinInput::GetCursor(&x, &y);
	return glm::vec2(x, y);
}

glm::vec2 Input::MouseDelta(bool pixels)
{
	if (pixels)
		return glm::vec2(mouseDeltaX, mouseDeltaY);
	else
	{
		return glm::vec2(
			mouseDeltaX / Window::width,
			mouseDeltaY / Window::height
		);
	}
}

void Input::ShowCursor(bool show)
{
	WinInput::CursorVisibility(show);
	cursorVisibility = show;
}

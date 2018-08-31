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
	//Private
	bool currentKeys[KEY_COUNT];
	bool pastKeys[KEY_COUNT];
	int currentMousePosX, currentMousePosY;
	int pastMousePosX, pastMousePosY;
}

void Input::Init()
{
	WinInput::Init(KeyEvent, Input::CursorEvent);
}

void Input::Update()
{
	memcpy(&pastKeys[0], &currentKeys[0], KEY_COUNT);

	pastMousePosX = currentMousePosX;
	pastMousePosY = currentMousePosY;
}

void Input::KeyEvent(Event event, Key key)
{
	currentKeys[(int)key] = (bool)event;
}

void Input::CursorEvent(int xPos, int yPos)
{
	currentMousePosX = xPos;
	currentMousePosY = yPos;
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
	if (pixels)
		return glm::vec2(currentMousePosX, currentMousePosY);
	else
	{
		return glm::vec2(
			(float)currentMousePosX / Window::width,
			(float)currentMousePosY / Window::height
		);
	}
}

glm::vec2 Input::GetMouseAxis(bool pixels)
{
	if (pixels)
	{
		return glm::vec2(
			(float)(currentMousePosX - pastMousePosX),
			(float)(currentMousePosY - pastMousePosY)
		);
	}
	else
	{
		return glm::vec2(
			(float)(currentMousePosX - pastMousePosX) / Window::width,
			(float)(currentMousePosY - pastMousePosY) / Window::height
		);
	}
}

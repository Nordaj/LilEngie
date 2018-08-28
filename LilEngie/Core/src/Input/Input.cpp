#include <unordered_map>
#include <string>
#include <glm/common.hpp>
#include "Platform/Windows/WinInput.h"
#include "Keys.h"
#include "Input.h"

#define KEY_COUNT 255

namespace Input
{
	//Private
	bool currentKeys[KEY_COUNT];
	bool pastKeys[KEY_COUNT];
}

void Input::Init()
{
	WinInput::Init(KeyEvent);
}

void Input::Update()
{
	memcpy(&pastKeys[0], &currentKeys[0], KEY_COUNT);
}

void Input::KeyEvent(Event event, Key key)
{
	currentKeys[(int)key] = (bool)event;
}

bool Input::GetKey(Key key)
{
	return false;
}

bool Input::GetKeyPress(Key key)
{
	return false;
}

bool Input::GetKeyUp(Key key)
{
	return false;
}

glm::vec2 Input::GetPointerPos()
{
	return glm::vec2(0, 0);
}

bool Input::GetMouse(MouseBtn btn)
{
	return false;
}

bool Input::GetMousePress(MouseBtn btn)
{
	return false;
}

bool Input::GetMouseUp(MouseBtn btn)
{
	return false;
}

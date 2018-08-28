#pragma once

#include <Input/Keys.h>

namespace WinInput
{
	typedef void(*KeyEventCallback)(Input::Event, Input::Key);

	void Init(KeyEventCallback keyEvCallback);
}

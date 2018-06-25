#pragma once

#include <glm/common.hpp>
#include "Character.h"

namespace TextHandler
{
	void Init();
	Character *GetChar(char c);
}

namespace Text = TextHandler;

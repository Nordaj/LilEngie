#pragma once

#include <unordered_map>
#include "Character.h"

//Holds all characters in hasmap for easy rendering
class Font
{
public:
	unsigned int texID;
	std::unordered_map<char, Character> characters;
};

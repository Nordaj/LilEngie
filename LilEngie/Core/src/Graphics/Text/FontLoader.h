#pragma once

#include <string>
#include <unordered_map>
#include "Character.h"

namespace FontLoader
{
	typedef std::unordered_map<char, Character> CharMap;

	//Returns 0 on success, 1 on fail
	int Load(const char *path, CharMap *map, std::string *texName);
}

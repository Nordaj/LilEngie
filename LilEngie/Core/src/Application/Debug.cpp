#include <iostream>
#include <Windows.h>
#include <Game/Game.h>
#include "Debug.h"

//TODO Use platform folder for this. its windows specific

void Debug::Popup(const char *message, DebugType type, bool exitGame)
{
	switch (type)
	{
		case DebugType::Error:
			MessageBox(NULL, message, "Something went wrong!", MB_OK | MB_ICONERROR);
			break;
		case DebugType::Warning:
			MessageBox(NULL, message, "Warning", MB_OK | MB_ICONWARNING);
			break;
		case DebugType::Log:
			MessageBox(NULL, message, "Hey...", MB_OK);
			break;
	}

	if (exitGame)
		Game::Close();
}

void Debug::Log(const char *message, DebugType type, bool exitGame)
{
	switch (type)
	{
		case DebugType::Error:
			std::cout << "ERROR: " << message << std::endl;
			break;
		case DebugType::Warning:
			std::cout << "WARNING: " << message << std::endl;
			break;
		case DebugType::Log:
			std::cout << message << std::endl;
			break;
	}

	if (exitGame)
		Game::Close();
}

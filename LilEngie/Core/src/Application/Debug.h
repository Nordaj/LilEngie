#pragma once

enum DebugType { Error, Warning, Log };

namespace Debug
{
	void Popup(const char *message, DebugType type = DebugType::Error, bool exitGame = true);
	void Log(const char *message, DebugType type = DebugType::Error, bool exitGame = false);
}

#define ERROR Debug::Popup
#define POPUP Debug::Popup
#define LOG Debug::Log

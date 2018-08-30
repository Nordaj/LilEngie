#pragma once

typedef void(*vFunction)();

namespace Game
{
	void Init(vFunction callback = nullptr);
	void Run(vFunction callback = nullptr);
	void Close();
}

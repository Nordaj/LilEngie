#include <iostream>

#include "Core/LilEngie.h"

int main()
{
	Game::Init();

	Renderer::SetClearColor(1, 0, 0, 1);

	Game::Run();
	Game::Close();

	return 0;
}

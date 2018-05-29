#include <iostream>

#include "Core/LilEngie.h"

int main()
{
	Game::Init();

	Renderer::SetClearColor(1, 0, 0, 1);
	
	//Create object
	GameObject obj = GameObject();
	Mesh mesh = Mesh(&obj);
	obj.AddComponent(mesh);
	ObjectManager::AddObject(&obj);

	//Access components stuff
	Mesh *m = (Mesh*)obj.GetComponent("Mesh");
	m->x = 5;

	//Debug testing
	std::cout << m->x << std::endl;

	Game::Run();
	Game::Close();

	return 0;
}

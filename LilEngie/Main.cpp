#include <iostream>

#include "Core/LilEngie.h"

int main()
{
	Game::Init();

	//-----OBJECT ONE-----//
	///Create object 
	GameObject obj = GameObject();
	ObjectManager::AddObject(obj);

	///Add transform
	Transform tran = Transform(obj);
	obj.AddComponent(tran);

	///Add mesh
	Mesh mesh = Mesh(obj);
	obj.AddComponent(mesh);

	///Setup mesh
	mesh.Setup(BaseMeshes::triangleVerts, BaseMeshes::triangleInd, "Resources/Unlit.shader");

	Game::Run();
	Game::Close();

	return 0;
}

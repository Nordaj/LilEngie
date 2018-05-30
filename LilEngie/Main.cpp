#include <iostream>
#include <vector>

#include "Core/LilEngie.h"

int main()
{
	//Create vertex array for a basic triangle
	std::vector<float> verts = {
		 0.0f,  0.5f,  0.0f, //0
		 0.5f, -0.5f,  0.0f, //1
		-0.5f, -0.5f,  0.0f, //3
	};

	std::vector<unsigned int> ind = {
		0, 1, 2
	};

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
	mesh.Setup(verts, ind, 0);

	Game::Run();
	Game::Close();

	return 0;
}

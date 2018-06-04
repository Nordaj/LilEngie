#include <iostream>
#include <string>

#include "Core/LilEngie.h"

int main()
{
	std::vector<float> verts;
	std::vector<unsigned int> inds;
	ModelLoader::LoadOBJ("Resources/MattyGun.obj", &verts, &inds);

	Game::Init();

	#pragma region Shaders/Mats
	//Create unlit shader
	shader unlit = Shaders::Create("Resources/Unlit.shader");

	//Create blue green material
	mat blue = Mats::Create(unlit);
	Mats::Get(blue)->AddColor("uColor", 0, 1, 1, 1);

	//Create red material
	mat red = Mats::Create(unlit);
	Mats::Get(red)->AddColor("uColor", 1, 0, 0, 1);
	#pragma endregion

	#pragma region BlueTorus
	//Create object with transform and mesh
	GameObject obj = GameObject();
	Transform tran = Transform(obj);
	Mesh mesh = Mesh(obj);
	
	//Setup mesh
	mesh.Setup(verts, inds, blue);
	
	//Move transform
	tran.transform = glm::translate(tran.transform, glm::vec3(0.5f, 0, 0));

	//Scale transform
	tran.transform = glm::scale(tran.transform, glm::vec3(0.2f, 0.2f, 0.2f));

	//Rotate transform
	//tran.transform = glm::rotate(tran.transform, glm::degrees(90.0f), glm::vec3(1, 0, 0));
	#pragma endregion

	#pragma region RedTriangle
	//Create object with transform and mesh
	GameObject left = GameObject();
	Transform leftTran = Transform(left);
	Mesh leftMesh = Mesh(left);

	//Setup mesh
	leftMesh.Setup(BaseMeshes::triangleVerts, BaseMeshes::triangleInd, red);

	//Move transform
	leftTran.transform = glm::translate(leftTran.transform, glm::vec3(-1.5f, 0.2f, 0));
	#pragma endregion

	#pragma region Camera
	//Create object with camera component
	GameObject camera = GameObject();
	Camera camCam = Camera(camera);

	//Move camera a tad
	camCam.position += glm::vec3(0, 0, 2);
	#pragma endregion

	Game::Run();
	Game::Close();

	return 0;
}

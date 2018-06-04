#include <iostream>
#include <string>

#include "Core/LilEngie.h"

int main()
{
	Game::Init();

	//Create unlit shader
	shader unlit = Shaders::Create("Resources/Unlit.shader");

	//Create blue green material
	mat blue = Mats::Create(unlit);
	Mats::Get(blue)->AddColor("uColor", 0, 1, 1, 1);

	//Create red material
	mat red = Mats::Create(unlit);
	Mats::Get(red)->AddColor("uColor", 1, 0, 0, 1);

	//-----OBJECT ONE-----//
	///Create object with transform and mesh
	GameObject obj = GameObject();
	Transform tran = Transform(obj);
	Mesh mesh = Mesh(obj);
	///Setup mesh
	mesh.Setup(BaseMeshes::triangleVerts, BaseMeshes::triangleInd, blue);
	///Move transform
	tran.transform = glm::translate(tran.transform, glm::vec3(0.5f, 0, 0));

	//-----OBJECT TWO-----//
	///Create object with transform and mesh
	GameObject left = GameObject();
	Transform leftTran = Transform(left);
	Mesh leftMesh = Mesh(left);
	///Setup mesh
	leftMesh.Setup(BaseMeshes::triangleVerts, BaseMeshes::triangleInd, red);
	///Move transform
	leftTran.transform = glm::translate(leftTran.transform, glm::vec3(-0.5f, 0.2f, 0));

	//-----CAMERA OBJECT-----//
	///Create object with camera component
	GameObject camera = GameObject();
	Camera camCam = Camera(camera);
	///Move camera a tad
	camCam.position += glm::vec3(0, 0, 2);

	Game::Run();
	Game::Close();

	return 0;
}

#include <iostream>
#include <string>

#include "Core/LilEngie.h"

int main()
{
	Game::Init();

	#pragma region AdditionLightStuff
	LightHandler::ambient = glm::vec3(0.1f, 0.1f, 0.1f);
	#pragma endregion

	#pragma region Shaders/Mats
	//Create unlit shader
	shader unlit = Shaders::Create("Resources/Diffuse.shader");

	//Create blue green material
	mat blue = Mats::Create(unlit);
	Mats::Get(blue)->AddColor("uColor", 0, 1, 1, 1);

	//Create red material
	mat red = Mats::Create(unlit);
	Mats::Get(red)->AddColor("uColor", 1, 0.4f, 0.05f, 1);
	#pragma endregion

	#pragma region BlueCube
	//Create object with transform and mesh
	GameObject obj = GameObject();
	Transform tran = Transform(obj);
	Mesh mesh = Mesh(obj);
	
	//Setup mesh
	mesh.Setup(BaseMeshes::cubeVertices, BaseMeshes::cubeIndices, blue);
	
	//Move transform
	tran.transform = glm::translate(tran.transform, glm::vec3(0, 0, 0));

	//Scale transform
	tran.transform = glm::scale(tran.transform, glm::vec3(1.0f, 1.0f, 1.0f));

	//Rotate transform
	tran.transform = glm::rotate(tran.transform, glm::degrees(10.0f), glm::vec3(0, 1, 0));
	#pragma endregion

	#pragma region PointLight
	GameObject light = GameObject();
	PointLight ptLight = PointLight(light);
	ptLight.pos = glm::vec3(0, 0, 2);
	ptLight.color = glm::vec3(0.2f, 1, 0.2f);
	ptLight.intensity = 0.5f;
	#pragma endregion

	#pragma region DirLight
	GameObject dirLight = GameObject();
	DirectionalLight dLight = DirectionalLight(dirLight);
	dLight.dir = glm::vec3(-0.2f, -1.0f, -0.3f);
	dLight.color = glm::vec3(1, 1, 1);
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

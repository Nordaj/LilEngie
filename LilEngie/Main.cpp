#include <iostream>
#include <string>

#include "Core/LilEngie.h"

int main()
{
	Game::Init();

	Renderer::SetClearColor(0.25f, 0.2f, 0.2f, 1);

	#pragma region AdditionLightStuff
	LightHandler::ambient = glm::vec3(0.1f, 0.1f, 0.1f);
	#pragma endregion

	#pragma region Importing
	Model gunModel = ModelLoader::Load("Resources/MattyGun.obj");
	#pragma endregion

	#pragma region Shaders/Mats
	//Create unlit shader
	shader unlit = Shaders::Create("Resources/Diffuse.shader");

	//Create blue green material
	mat tan = Mats::Create(unlit);
	Mats::Get(tan)->AddColor("uColor", 0.75f, 0.6f, 0.42f, 1);

	//Create red material
	mat red = Mats::Create(unlit);
	Mats::Get(red)->AddColor("uColor", 1, 0.4f, 0.05f, 1);
	#pragma endregion

	#pragma region Gun
	//Create object with transform and mesh
	GameObject obj = GameObject();
	Transform tran = Transform(obj);
	Mesh mesh = Mesh(obj);
	
	//Setup mesh
	mesh.Setup(gunModel.vertices, gunModel.indices, tan);
	
	//Move transform
	tran.transform = glm::translate(tran.transform, glm::vec3(0.5f, 0, 0));

	//Scale transform
	tran.transform = glm::scale(tran.transform, glm::vec3(0.3f, 0.3f, 0.3f));

	//Rotate transform
	tran.transform = glm::rotate(tran.transform, glm::radians(20.0f), glm::vec3(0, 1, 0));
	tran.transform = glm::rotate(tran.transform, glm::radians(10.0f), glm::vec3(0, 0, 1));
	#pragma endregion

	#pragma region PointLight
	GameObject light = GameObject();
	PointLight ptLight = PointLight(light);
	ptLight.pos = glm::vec3(0, 0, 2);
	ptLight.color = glm::vec3(1, 0.95f, 0.95f);
	ptLight.intensity = 0.5f;
	#pragma endregion

	#pragma region DirLight
	GameObject dirLight = GameObject();
	DirectionalLight dLight = DirectionalLight(dirLight);
	dLight.dir = glm::vec3(-0.2f, -1.0f, -0.3f);
	dLight.color = glm::vec3(1, 0.95f, 0.95f);
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

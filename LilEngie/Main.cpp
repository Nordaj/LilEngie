#include <iostream>
#include <string>

#include "Core/LilEngie.h"

int main()
{
	Game::Init();

	Renderer::SetClearColor(0.2f, 0.2f, 0.2f, 1);

	#pragma region AdditionLightStuff
	LightHandler::ambient = glm::vec3(0.1f, 0.1f, 0.1f);
	#pragma endregion

	#pragma region Loading
	//Load gun model
	Model gunModel = ModelLoader::Load("Resources/MattyGun.obj");

	//Load gears
	Model gearsModel = ModelLoader::Load("Resources/RustyGearsMatty.fbx");

	//Load rust texture
	Texture rust = Texture("Resources/Rusty.png");
	#pragma endregion

	#pragma region Shaders/Mats
	//Create unlit shader
	shader diffuse = Shaders::Create("Resources/Diffuse.shader");

	//Create blue green material
	mat tan = Mats::Create(diffuse);
	Mats::Get(tan)->AddColor("uColor", 0.75f, 0.6f, 0.42f, 1);

	//Create red material
	mat rustMat = Mats::Create(diffuse);
	Mats::Get(rustMat)->AddColor("uColor", 1, 1, 1, 1);
	Mats::Get(rustMat)->AddTexture("uMainTex", rust);
	#pragma endregion

	#pragma region Gears
	//Create object with transform and mesh
	GameObject obj = GameObject();
	Transform tran = Transform(obj);
	Mesh mesh = Mesh(obj);
	
	//Setup mesh
	mesh.Setup(gearsModel.vertices, gearsModel.indices, rustMat);
	
	//Move transform
	tran.transform = glm::translate(tran.transform, glm::vec3(0, 0, 0));

	//Scale transform
	tran.transform = glm::scale(tran.transform, glm::vec3(0.5f, 0.5f, 0.5f));

	//Rotate transform
	tran.transform = glm::rotate(tran.transform, glm::radians(45.0f), glm::vec3(0, 1, 0));
	tran.transform = glm::rotate(tran.transform, glm::radians(45.0f), glm::vec3(0, 0, 1));
	#pragma endregion

	#pragma region PointLight
	GameObject light = GameObject();
	PointLight ptLight = PointLight(light);
	ptLight.pos = glm::vec3(0, 0, 2);
	ptLight.color = glm::vec3(1, 0.95f, 0.95f);
	ptLight.intensity = 0.5f;
	#pragma endregion

	#pragma region SpotLight
	GameObject spotLightObj = GameObject();
	SpotLight sLight = SpotLight(spotLightObj);
	sLight.pos = glm::vec3(0, 0, 3);
	sLight.color = glm::vec3(1, 1, 1);
	sLight.angle = glm::cos(glm::radians(20.0f));
	#pragma endregion

	#pragma region DirLight
	/*
	GameObject dirLight = GameObject();
	DirectionalLight dLight = DirectionalLight(dirLight);
	dLight.dir = glm::vec3(-0.2f, -1.0f, -0.3f);
	dLight.color = glm::vec3(1, 0.95f, 0.95f);
	*/
	#pragma endregion

	#pragma region Camera
	//Create object with camera component
	GameObject camera = GameObject();
	Camera camCam = Camera(camera);

	//Move camera a tad
	camCam.position += glm::vec3(0, 0, 3);
	#pragma endregion

	Game::Run();
	Game::Close();

	return 0;
}

#include <iostream>
#include <string>

#include "Core/LilEngie.h"

//TODO
///Scene loading
///Lights and camera components should work from transform component
///Better input system
///Use heap for Shaders, Mats, Models, Objects, Components, and Scenes

//CHANGES
///

void Update();

Scene mainScene;
Scene secondScene;

int main()
{
	Game::Init();

	#pragma region Setup
	Renderer::SetClearColor(0.05f, 0.05f, 0.05f, 1);
	LightHandler::SetAmbient(glm::vec3(0.05f, 0.05f, 0.05f));

	SceneLoader::LoadScene("Resources/TestScene.lilscn");
	ObjectManager::SetScene(&mainScene);
	#pragma endregion

	//==========FIRST SCENE==========//

	#pragma region Gears
	//Create object with transform and mesh
	GameObject obj = GameObject();
	Transform tran = Transform(obj);
	Mesh mesh = Mesh(obj);
	
	//Setup mesh
	mesh.Setup(Models::Get("gearsModel"), Mats::Get("rustMaterial"));
	
	//Move transform
	tran.position = glm::vec3(0, 0, 0);

	//Scale transform
	tran.scale = glm::vec3(0.5f, 0.5f, 0.5f);

	//Rotate transform
	//(pitch, yaw, roll) X->Y->Z
	tran.rotation = glm::quat(glm::vec3(glm::radians(30.0f), glm::radians(30.0f), glm::radians(0.0f)));
	#pragma endregion

	#pragma region PointLight
	GameObject light = GameObject();
	Transform lightTran = Transform(light);
	Mesh lightMesh = Mesh(light);
	PointLight ptLight = PointLight(light);

	lightMesh.Setup(&BaseMeshes::cube, Mats::Get("unlitMaterial"));

	lightTran.scale = glm::vec3(0.05f, 0.05f, 0.05f);
	lightTran.rotation = glm::quat(glm::vec3(glm::radians(45.0f), glm::radians(45.0f), glm::radians(45.0f)));
	lightTran.position = glm::vec3(0, 0, 2);

	ptLight.pos = glm::vec3(0, 0, 2);
	ptLight.color = glm::vec3(1, 1, 1);
	ptLight.intensity = 0.5f;
	#pragma endregion

	#pragma region Camera
	//Create object with camera component
	GameObject camera = GameObject();
	Camera camCam = Camera(camera);

	//Move camera a tad
	camCam.position += glm::vec3(0, 0, 3);
	#pragma endregion

	//==========SECOND SCENE==========//

	#pragma region Cube
	GameObject cubeObj = GameObject(&secondScene);
	Transform cubeTransform = Transform(cubeObj);
	Mesh cubeMesh = Mesh(cubeObj);

	cubeMesh.Setup(&BaseMeshes::cube, Mats::Get("unlitMaterial"));

	cubeTransform.rotation = glm::quat(glm::vec3(glm::radians(45.0f), glm::radians(45.0f), glm::radians(0.0f)));
	cubeTransform.scale = glm::vec3(0.2f, 0.2f, 0.2f);
	#pragma endregion

	Game::Run(Update);
	Game::Close();

	return 0;
}

void Update()
{
	if (Input::GetKey(Key::Space))
	{
		//Swith to second if not on
		if (ObjectManager::GetCurrent() != &secondScene)
			ObjectManager::SetScene(&secondScene);
	}
	else if (Input::GetKey(Key::A))
	{
		//Switch to main if not on
		if (ObjectManager::GetCurrent() != &mainScene)
			ObjectManager::SetScene(&mainScene);
	}
}

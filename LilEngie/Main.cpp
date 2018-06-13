#include <iostream>
#include <string>

#include "Core/LilEngie.h"

//TODO
///Lights and camera components should work from transform component
///Better input system
///Use heap for Shaders, Mats, Models, Objects, Components, and Scenes

//CHANGES
///Scene changing	X
///Update callback	X
///Input			X

void Update();

Scene mainScene;
Scene secondScene;

int main()
{
	Game::Init();

	Renderer::SetClearColor(0.05f, 0.05f, 0.05f, 1);
	LightHandler::SetAmbient(glm::vec3(0.05f, 0.05f, 0.05f));

	#pragma region Loading
	//Load gun model
	Model gunModel = ModelLoader::Load("Resources/MattyGun.obj");

	//Load gears
	Model gearsModel = ModelLoader::Load("Resources/RustyGearsMatty.fbx");

	//Load rust texture
	Texture rust = Texture("Resources/Rusty.png");
	#pragma endregion

	#pragma region Shaders/Mats
	//Create diffuse shader
	shader diffuse = Shaders::Create("Resources/Diffuse.shader");

	//Create unlit shader
	shader unlit = Shaders::Create("Resources/Unlit.shader");

	//Create blue green material
	mat tan = Mats::Create(diffuse);
	Mats::Get(tan)->AddColor("uColor", 0.75f, 0.6f, 0.42f, 1);

	//Create red material
	mat rustMat = Mats::Create(diffuse);
	Mats::Get(rustMat)->AddColor("uColor", 1, 1, 1, 1);
	Mats::Get(rustMat)->AddTexture("uMainTex", rust);

	//Create unlit material
	mat unlitWhite = Mats::Create(unlit);
	Mats::Get(unlitWhite)->AddColor("uColor", 1, 1, 1, 1);
	#pragma endregion

	#pragma region Scene
	ObjectManager::SetScene(&mainScene);
	#pragma endregion

	//==========FIRST SCENE==========//

	#pragma region Gears
	//Create object with transform and mesh
	GameObject obj = GameObject();
	Transform tran = Transform(obj);
	Mesh mesh = Mesh(obj);
	
	//Setup mesh
	mesh.Setup(gearsModel.vertices, gearsModel.indices, rustMat);
	
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

	lightMesh.Setup(BaseMeshes::cubeVertices, BaseMeshes::cubeIndices, unlitWhite);

	lightTran.scale = glm::vec3(0.05f, 0.05f, 0.05f);
	lightTran.rotation = glm::quat(glm::vec3(glm::radians(45.0f), glm::radians(45.0f), glm::radians(45.0f)));
	lightTran.position = glm::vec3(0, 0, 2);

	ptLight.pos = glm::vec3(0, 0, 2);
	ptLight.color = glm::vec3(1, 1, 1);
	ptLight.intensity = 0.5f;
	#pragma endregion

	#pragma region SpotLight
	/*
	GameObject spotLightObj = GameObject();
	SpotLight sLight = SpotLight(spotLightObj);
	sLight.pos = glm::vec3(0, 0, 3);
	sLight.color = glm::vec3(1, 1, 1);
	sLight.angle = glm::cos(glm::radians(20.0f));
	*/
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

	//==========SECOND SCENE==========//

	#pragma region Cube
	GameObject cubeObj = GameObject(&secondScene);
	Transform cubeTransform = Transform(cubeObj);
	Mesh cubeMesh = Mesh(cubeObj);

	cubeMesh.Setup(BaseMeshes::cubeVertices, BaseMeshes::cubeIndices, unlitWhite);

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

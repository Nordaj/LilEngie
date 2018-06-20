#include <iostream>
#include <string>
#include "Core/LilEngie.h"

void Update();
Scene mainScene;
Scene secondScene;

int main()
{
	Game::Init();

	Renderer::SetClearColor(0.05f, 0.05f, 0.05f, 1);
	LightHandler::SetAmbient(glm::vec3(0.05f, 0.05f, 0.05f));

	SceneLoader::LoadScene("Resources/TestScene.lilscn", &mainScene);
	SceneLoader::LoadScene("Resources/SecondScene.lilscn", &secondScene);
	ObjectManager::SetScene(&mainScene);

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

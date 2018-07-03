#include <iostream>
#include <string>
#include "Core/LilEngie.h"

void Update();
Scene *mainScene;
Scene *secondScene;

//Changes
///TextHandler is a class, part of scenes -
///Scenes/objects now use heap -
///Text only render if its current scene -

int main()
{
	Game::Init();

	mainScene = new Scene();
	secondScene = new Scene();

	Renderer::SetClearColor(0.05f, 0.05f, 0.05f, 1);
	LightHandler::SetAmbient(glm::vec3(0.05f, 0.05f, 0.05f));

	SceneLoader::LoadScene("Resources/Scenes/TestScene.lilscn", mainScene);
	SceneLoader::LoadScene("Resources/Scenes/SecondScene.lilscn", secondScene);
	SceneManager::SetScene(mainScene);

	Game::Run(Update);
	Game::Close();

	//A way to automate this would be nice...
	delete mainScene;
	delete secondScene;

	return 0;
}

void Update()
{
	if (Input::GetKey(Key::Space))
	{
		//Swith to second if not on
		if (SceneManager::GetCurrent() != secondScene)
			SceneManager::SetScene(secondScene);
	}
	else if (Input::GetKey(Key::A))
	{
		//Switch to main if not on
		if (SceneManager::GetCurrent() != mainScene)
			SceneManager::SetScene(mainScene);
	}

	if (Input::GetKey(Key::C))
		Game::Close();

	//Spin
	Transform *t = (Transform*)mainScene->GetObject("gearsObject")->GetComponent("Transform");
	t->rotation = glm::rotate(t->rotation, glm::radians(0.1f), glm::vec3(0, 1, 0));
}

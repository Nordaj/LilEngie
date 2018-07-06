#include <iostream>
#include <string>
#include "Core/LilEngie.h"

//FIX BEFORE MIDNIGHT

void Update();
Scene *mainScene = nullptr;
Scene *secondScene = nullptr;
bool space;

//Changes
///

int main()
{
	Game::Init();

	Renderer::SetClearColor(0.1, 0.1, 0.1, 1);
	LightHandler::SetAmbient(glm::vec3(0.2, 0.2, 0.2));

	mainScene = new Scene();
	secondScene = new Scene();

	SceneLoader::LoadScene("Resources/Scenes/TestScene.lilscn", mainScene);
	SceneManager::SetScene(mainScene);

	Game::Run(Update);
	Game::Close();

	if (mainScene != nullptr)
	{
		mainScene->Unload();
		delete mainScene;
	}

	if (secondScene != nullptr)
	{
		secondScene->Unload();
		delete secondScene;
	}

	return 0;
}

void Update()
{
	//Scene toggling
	if (Input::GetKey(Key::Space))
	{
		if (!space)
		{
			if (SceneManager::GetCurrent() == mainScene)
			{
				//Clean up other scene
				mainScene->Unload();
				delete mainScene;
				mainScene = nullptr;

				//Setup new scene
				secondScene = new Scene();
				SceneLoader::LoadScene("Resources/Scenes/SecondScene.lilscn", secondScene);
				SceneManager::SetScene(secondScene);
			}
			else if (SceneManager::GetCurrent() == secondScene)
			{
				//Clean up other scene
				secondScene->Unload();
				delete secondScene;
				secondScene = nullptr;

				//Setup new scene
				mainScene = new Scene();
				SceneLoader::LoadScene("Resources/Scenes/TestScene.lilscn", mainScene);
				SceneManager::SetScene(mainScene);
			}
		}
		else
		{
			space = true;
		}
	}
	else
	{
		space = false;
	}

	//Close on C
	if (Input::GetKey(Key::C))
		Game::Close();

	//Spin if im in main scene
	if (SceneManager::GetCurrent() == mainScene)
	{
		Transform *t = (Transform*)mainScene->GetObject("gearsObject")->GetComponent("Transform");
		t->rotation = glm::rotate(t->rotation, glm::radians(0.1f), glm::vec3(0, 1, 0));
	}
}

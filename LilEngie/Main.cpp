#include <iostream>
#include <string>
#include "Core/LilEngie.h"

void Update();

Scene *mainScene = nullptr;
Scene *secondScene = nullptr;
bool space;
bool fKey;
bool fullScreen;

//Changes
///

int main()
{
	Game::Init();
	Scenes::LoadScene("Resources/Scenes/TestScene.lilscn", &mainScene);
	Game::Run(Update);
	Game::Close();

	return 0;
}

void Update()
{
	//Scene toggling
	if (Input::GetKey(Key::Space))
	{
		if (!space)
		{
			if (Scenes::GetCurrent() == mainScene)
			{
				Scenes::UnloadScene(&mainScene);
				Scenes::LoadScene("Resources/Scenes/SecondScene.lilscn", &secondScene);
			}
			else if (SceneManager::GetCurrent() == secondScene)
			{
				Scenes::UnloadScene(&secondScene);
				Scenes::LoadScene("Resources/Scenes/TestScene.lilscn", &mainScene);
			}

			space = true;
		}
	}
	else
		space = false;

	//Fullscreen mode
	if (Input::GetKey(Key::F))
	{
		if (!fKey)
		{
			//Toggle
			Window::SetFullScreen(!fullScreen);
			fullScreen = !fullScreen;

			fKey = true;
		}
	}
	else
		fKey = false;

	//Close on C
	if (Input::GetKey(Key::C))
		Game::Close();

	//Spin if im in main scene
	if (SceneManager::GetCurrent() == mainScene)
	{
		//Get pointer to transform
		GameObject *g = mainScene->GetObject("gearsObject");
		Transform *t = (Transform*)g->GetComponent("Transform");

		t->rotation = glm::rotate(t->rotation, glm::radians(0.1f), glm::vec3(0, 1, 0));
	}
}

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
///Specularity map
///Time

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

	//Move camera if im in scene
	if (SceneManager::GetCurrent() == mainScene)
	{
		mainScene->GetCam()->GetTransform()->position = glm::vec3(
			mainScene->GetCam()->GetTransform()->position.x,
			(glm::sin(Time::Get(Time::Unit::Seconds) * 3) - 0.5f) * 0.2f,
			mainScene->GetCam()->GetTransform()->position.z
		);
	}
}

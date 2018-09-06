#include <iostream>
#include <string>
#include "Core/LilEngie.h"

///Changes:

void Update();
void Start();

Scene *mainScene = nullptr;
Scene *secondScene = nullptr;
Scene *d3dScene = nullptr;
bool fullScreen;

int main()
{
	Game::Init(Start);
	//Scenes::LoadScene("Resources/Scenes/TestScene.lilscn", &mainScene);
	Scenes::LoadScene("Resources/Scenes/DXScene.lilscn", &d3dScene);
	Game::Run(Update);
	Game::Close();

	return 0;
}

void Start()
{ }

void Update()
{
	//Scene toggling
	if (Input::GetKeyUp(Key::Space))
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
	}

	//Fullscreen mode
	if (Input::GetKeyUp(Key::F))
	{
		//Toggle
		Window::SetFullScreen(!fullScreen);
		fullScreen = !fullScreen;
	}

	//Close on C
	if (Input::GetKeyUp(Key::C))
		Game::Close();

	//Lock cursor with L
	if (Input::GetKeyUp(Key::L))
	{
		Input::lockCursorMode = !Input::lockCursorMode;
		Input::ShowCursor(!Input::cursorVisibility);
	}

	//Rotate shield if in second scene
	if (Scenes::GetCurrent() == secondScene)
	{
		Transform *t = (Transform*)secondScene->GetObject("shieldObj")->GetComponent("Transform");
		t->rotation = glm::rotate(t->rotation, glm::radians(20 * Time::deltaTime), glm::vec3(0, 1, 0));
	}
}

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

	SceneLoader::LoadScene("Resources/Scenes/TestScene.lilscn", &mainScene);
	SceneLoader::LoadScene("Resources/Scenes/SecondScene.lilscn", &secondScene);
	SceneManager::SetScene(&mainScene);

	TextRenderer tr = TextRenderer();
	tr.text = "This is some sample text...";
	tr.scene = &mainScene;
	tr.color = glm::vec4(0, 1, 1, 1);
	tr.fontName = "Ariel";
	tr.position = glm::vec2(-1, 1);
	tr.materialName = "textMaterial";
	tr.size = 130;
	TextHandler::texts.push_back(tr);

	Game::Run(Update);
	Game::Close();

	return 0;
}

void Update()
{
	if (Input::GetKey(Key::Space))
	{
		//Swith to second if not on
		if (SceneManager::GetCurrent() != &secondScene)
			SceneManager::SetScene(&secondScene);
	}
	else if (Input::GetKey(Key::A))
	{
		//Switch to main if not on
		if (SceneManager::GetCurrent() != &mainScene)
			SceneManager::SetScene(&mainScene);
	}

	if (Input::GetKey(Key::C))
		Game::Close();

	//Spin
	Transform *t = (Transform*)mainScene.GetObject("gearsObject")->GetComponent("Transform");
	t->rotation = glm::rotate(t->rotation, glm::radians(0.1f), glm::vec3(0, 1, 0));
}

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <Entity/Components/Camera.h>
#include <Entity/Components/Mesh.h>
#include <Entity/GameObject.h>
#include <Graphics/LightHandler.h>
#include <Graphics/Renderer.h>
#include <Application/Debug.h>
#include "Scene.h"

Scene::Scene()
{ }

Scene::~Scene()
{
	if (isLoaded)
		Debug::Popup("Unload function not called for scene.", DebugType::Warning, false);
}

GameObject *Scene::AddObject(std::string name)
{
	objects.insert(std::make_pair(name, new GameObject(this)));
	return objects[name];
}

GameObject *Scene::GetObject(std::string name)
{
	return objects[name];
}

void Scene::AddToQueue(Mesh *m)
{
	renderQueue.push_back(m);
}

Camera* Scene::GetCam()
{
	return currentCamera;
}

void Scene::SetCurrentCamera(Camera *cam)
{
	currentCamera = cam;
}

std::vector<Mesh*> *Scene::GetQueue()
{
	return &renderQueue;
}

void Scene::Start()
{
	//Start all objects
	std::map<std::string, GameObject*>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		it->second->Start();
	}

	//Set ambient and clear color
	LightHandler::SetAmbient(ambient);
	Renderer::SetClearColor(clearColor.r, clearColor.g, clearColor.b, 1);
}

void Scene::Update()
{
	std::map<std::string, GameObject*>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		it->second->Update();
	}
}

void Scene::Close()
{
	LightHandler::Clean();
}

void Scene::Unload()
{
	isLoaded = false;
	Close();

	//Delete all objects
	std::map<std::string, GameObject*>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
		delete it->second;

	//Clear object map
	objects.clear();

	//Clear render queue
	renderQueue.clear();

	//Set current camera to nullptr
	currentCamera = nullptr;

	//Dump up all handlers
	shaders.Clean();
	models.Clean();
	textures.Clean();
	materials.Clean();
	texts.Clean();
}

#include <string>
#include <map>
#include <vector>
#include <Entity/Components/Camera.h>
#include <Entity/Components/Mesh.h>
#include <Entity/GameObject.h>
#include "Scene.h"

Scene::Scene()
{ }

GameObject *Scene::AddObject(std::string name)
{
	objects.insert(std::make_pair(name, GameObject(this)));
	return &objects[name];
}

GameObject *Scene::GetObject(std::string name)
{
	return &objects[name];
}

void Scene::AddToQueue(Mesh *m)
{
	renderQueue.push_back(m);
}

Camera* Scene::GetCam()
{
	//I NEED TO FIGURE OUT WHATS WRONG HERE
	return currentCamera;
}

void Scene::SetCurrentCamera(Camera *cam)
{
	currentCamera = cam;
}

std::vector<Mesh*>* Scene::GetQueue()
{
	return &renderQueue;
}

void Scene::Start()
{
	std::map<std::string, GameObject>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		it->second.Start();
	}
}

void Scene::Update()
{
	std::map<std::string, GameObject>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		it->second.Update();
	}
}

void Scene::Close()
{
	//TODO
	///Not sure what id need, probably remove all objects from render queue
}

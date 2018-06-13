#include <vector>
#include <Entity/Components/Camera.h>
#include <Entity/Components/Mesh.h>
#include "Scene.h"

Scene::Scene(std::vector<GameObject*> objs)
	:objects(objs)
{ }

void Scene::AddObject(GameObject &obj)
{
	objects.push_back(&obj);
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

std::vector<Mesh*>* Scene::GetQueue()
{
	return &renderQueue;
}

void Scene::Start()
{
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Start();
	}
}

void Scene::Update()
{
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update();
	}
}

void Scene::Close()
{
	//TODO
	///Not sure what id need, probably remove all objects from render queue
}

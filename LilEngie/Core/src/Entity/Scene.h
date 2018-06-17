#pragma once

#include <vector>
#include <string>
#include <map>
#include <Entity/Components/Mesh.h>
#include <Entity/Components/Camera.h>
#include "GameObject.h"

class Scene
{
private:
	std::map<std::string, GameObject> objects;
	std::vector<Mesh*> renderQueue;
	Camera *currentCamera;

public:
	Scene();

	GameObject *AddObject(std::string name);
	GameObject *GetObject(std::string name);
	void AddToQueue(Mesh *m);
	Camera* GetCam();
	void SetCurrentCamera(Camera *cam);
	std::vector<Mesh*>* GetQueue();
	void Start();
	void Update();
	void Close(); 
};

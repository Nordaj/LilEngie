#pragma once

#include <vector>
#include <Entity/Components/Mesh.h>
#include <Entity/Components/Camera.h>
#include "GameObject.h"

class Scene
{
private:
	std::vector<GameObject*> objects;
	std::vector<Mesh*> renderQueue;
	Camera *currentCamera;

public:
	Scene(std::vector<GameObject*> objs = std::vector<GameObject*>());

	void AddObject(GameObject &obj);
	void AddToQueue(Mesh *m);
	Camera* GetCam();
	void SetCurrentCamera(Camera *cam);
	std::vector<Mesh*>* GetQueue();
	void Start();
	void Update();
	void Close();
};

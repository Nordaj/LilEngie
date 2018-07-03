#pragma once

#include <vector>
#include <string>
#include <map>
#include <Entity/Components/Mesh.h>
#include <Entity/Components/Camera.h>
#include <Graphics/ShaderHandler.h>
#include <Graphics/ModelHandler.h>
#include <Graphics/TextureHandler.h>
#include <Graphics/MaterialHandler.h>
#include <Graphics/Text/TextHandler.h>
#include "GameObject.h"

class Scene
{
private:
	std::map<std::string, GameObject> objects;
	std::vector<Mesh*> renderQueue;
	Camera *currentCamera;

public:
	ShaderHandler shaders;
	ModelHandler models;
	TextureHandler textures;
	MaterialHandler materials;
	TextHandler texts;

	Scene();

	GameObject *AddObject(std::string name);
	GameObject *GetObject(std::string name);
	void AddToQueue(Mesh *m);
	Camera* GetCam();
	void SetCurrentCamera(Camera *cam);
	std::vector<Mesh*> *GetQueue();
	void Start();
	void Update();
	void Close(); 
};

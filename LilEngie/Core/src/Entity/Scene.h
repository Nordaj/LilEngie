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
	std::map<std::string, GameObject*> objects;
	std::vector<Mesh*> renderQueue;
	Camera *currentCamera;

public:
	bool isLoaded;
	ShaderHandler shaders;
	ModelHandler models;
	TextureHandler textures;
	MaterialHandler materials;
	TextHandler texts;
	glm::vec3 ambient = { 0.1f, 0.1f, 0.1f };
	glm::vec3 clearColor = { 0.1f, 0.1f, 0.1f };

	Scene();
	~Scene();

	GameObject *AddObject(std::string name);
	GameObject *GetObject(std::string name);
	void AddToQueue(Mesh *m);
	Camera* GetCam();
	void SetCurrentCamera(Camera *cam);
	std::vector<Mesh*> *GetQueue();
	void Start();
	void Update();
	//Closing a scene dumps any resources from being currently used. 
	//This does not unload. To unload a scene, use Unload
	void Close(); 
	//Unloading a scene closes then cleans up any loaded resources and objects.
	//In order to use the scene again, you will need to call SceneLoader::LoadScene()
	void Unload();
};

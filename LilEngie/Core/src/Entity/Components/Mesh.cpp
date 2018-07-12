#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <Entity/Component.h>
#include <Entity/GameObject.h>
#include <Graphics/MeshRenderer.h>
#include <Graphics/Renderer.h>
#include <Graphics/UniformHandler.h>
#include <Graphics/MaterialHandler.h>
#include <Graphics/ModelHandler.h>
#include <Graphics/Model.h>
#include <Application/Debug.h>
#include "Transform.h"
#include "Mesh.h"

Mesh::Mesh(GameObject *obj)
	:Component(obj)
{
	//Make sure i have a transform
	//TODO: figure out how to remove myself instead
	if (obj->GetComponent("Transform") == nullptr)
		LOG("Don't add me til you get a transform", Warning, false);

	//Keep track of my transform
	transform = (Transform*)obj->GetComponent(Transform::GetTypeStatic());
}

void Mesh::Setup(const char *model, const char *material)
{
	obj->GetMyScene()->materials.Get(material);

	//Setup mesh renderer
	meshRenderer.Setup(
		obj->GetMyScene()->models.Get(model)->vertices, 
		obj->GetMyScene()->models.Get(model)->indices,
		obj->GetMyScene()->materials.Get(material));

	//Add to render queue
	obj->GetMyScene()->AddToQueue(this);
}

void Mesh::Setup(Model *model, const char *material)
{
	//Setup mesh renderer
	meshRenderer.Setup(model->vertices, model->indices, obj->GetMyScene()->materials.Get(material));

	//Add to render queue
	obj->GetMyScene()->AddToQueue(this);
}

MeshRenderer* Mesh::GetRenderer()
{
	return &meshRenderer;
}

glm::mat4* Mesh::GetTransformation()
{
	return &transform->GetModel();
}

void Mesh::Draw(glm::mat4 &v, glm::mat4 &p, glm::vec3 &camPos)
{
	glm::mat4 MVP = p * v * transform->GetModel();
	glm::mat4 model = transform->GetModel();
	meshRenderer.Draw(MVP, model, camPos);
}

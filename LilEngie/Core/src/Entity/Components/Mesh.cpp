#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <Entity/Component.h>
#include <Entity/GameObject.h>
#include <Graphics/MeshRenderer.h>
#include <Graphics/Renderer.h>
#include <Graphics/UniformHandler.h>
#include <Graphics/Model.h>
#include "Transform.h"
#include "Mesh.h"

Mesh::Mesh(GameObject &obj)
	:Component(obj)
{
	//Make sure i have a transform
	//TODO: figure out how to remove myself instead
	if (obj.GetComponent("Transform") == nullptr)
		std::cout << "Don't add me til you get a transform" << std::endl;

	//Keep track of my transform
	transform = (Transform*)obj.GetComponent(Transform::GetTypeStatic());
}

void Mesh::Setup(Model *model, int material)
{
	//Setup mesh renderer
	meshRenderer.Setup(model->vertices, model->indices, material);

	//Add to render list
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

void Mesh::Draw(glm::mat4 &v, glm::mat4 &p)
{
	glm::mat4 MVP = p * v * transform->GetModel();
	glm::mat4 model = transform->GetModel();
	meshRenderer.Draw(MVP, model);
}

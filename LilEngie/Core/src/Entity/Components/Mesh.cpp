#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <Entity/Component.h>
#include <Entity/GameObject.h>
#include <Graphics/MeshRenderer.h>
#include <Graphics/Renderer.h>
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

void Mesh::Setup(std::vector<float> v, std::vector<unsigned int> i, std::string shaderPath)
{
	//Setup mesh renderer
	meshRenderer.Setup(v, i, shaderPath);

	//Add to render list
	Renderer::AddMesh(*this);
}

MeshRenderer& Mesh::GetRenderer()
{
	return meshRenderer;
}

glm::mat4& Mesh::GetTransformation()
{
	return transform->transformation;
}

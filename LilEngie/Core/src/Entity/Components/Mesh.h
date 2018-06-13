#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <Entity/Component.h>
#include <Graphics/MeshRenderer.h>
#include <Graphics/Material.h>
#include <Graphics/Model.h>
#include "Transform.h"

class Mesh : public Component
{
private:
	MeshRenderer meshRenderer;
	Transform *transform;

public:
	Mesh(GameObject &obj);

	void Setup(Model *model, int material);
	MeshRenderer* GetRenderer();
	glm::mat4* GetTransformation();
	void Draw(glm::mat4 &v, glm::mat4 &p);

	//Standard component methods
	static std::string GetTypeStatic() { return "Mesh"; }
	std::string GetType() { return GetTypeStatic(); }
	void* Get() { return this; }
};

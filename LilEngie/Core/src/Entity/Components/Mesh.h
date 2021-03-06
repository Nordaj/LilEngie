#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <Entity/Component.h>
#include <Graphics/MeshRenderer.h>
#include <Graphics/Model.h>
#include "Transform.h"

class Mesh : public Component
{
private:
	MeshRenderer meshRenderer;
	Transform *transform;

public:
	Mesh(GameObject *obj);

	void Setup(const char *model, const char *material);
	void Setup(Model *model, const char *material);
	MeshRenderer* GetRenderer();
	glm::mat4* GetTransformation();
	void Draw(glm::mat4 &v, glm::mat4 &p, glm::vec3 &camPos);

	COMPONENT_ID("Mesh")
};

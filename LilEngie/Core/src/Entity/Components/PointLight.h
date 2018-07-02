#pragma once

#include <Entity/Component.h>
#include <Entity/GameObject.h>
#include <glm/glm.hpp>

class PointLight : public Component
{
public:
	glm::vec3 pos = { 0, 0, 0 };
	glm::vec3 color = { 1, 1, 1 };
	float intensity = 1;

	PointLight(GameObject *obj);
	void Start();

	COMPONENT_ID("PointLight")
};

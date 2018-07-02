#pragma once

#pragma once

#include <Entity/Component.h>
#include <Entity/GameObject.h>
#include <glm/glm.hpp>

class DirectionalLight : public Component
{
public:
	glm::vec3 dir = { 0, 0, -1 };
	glm::vec3 color = { 1, 1, 1 };
	float intensity = 1;

	DirectionalLight(GameObject *obj);
	void Start();

	COMPONENT_ID("DirectionalLight")
};

#pragma once

#include <glm/glm.hpp>
#include <Entity/Component.h>

class SpotLight : public Component
{
public:
	glm::vec3 pos = { 0, 0, 0 };
	glm::vec3 dir = { 0, 0, -1 };
	glm::vec3 color = { 1, 1, 1 };
	float intensity = 1;
	float angle = glm::cos(glm::radians(10.0f));

	SpotLight(GameObject *obj);
	void Start();

	COMPONENT_ID("SpotLight")
};

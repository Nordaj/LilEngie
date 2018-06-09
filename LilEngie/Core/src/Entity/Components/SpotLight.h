#pragma once

#include <glm/glm.hpp>
#include <Entity/Component.h>

class SpotLight : public Component
{
public:
	glm::vec3 pos;
	glm::vec3 dir;
	glm::vec3 color;
	float intensity;
	float angle;

	SpotLight(GameObject &obj);

	//Standard component methods
	static std::string GetTypeStatic() { return "SpotLight"; }
	std::string GetType() { return GetTypeStatic(); }
	void* Get() { return this; }
};

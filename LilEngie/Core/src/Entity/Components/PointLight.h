#pragma once

#include <Entity/Component.h>
#include <Entity/GameObject.h>
#include <glm/glm.hpp>

class PointLight : public Component
{
public:
	glm::vec3 pos;
	glm::vec3 color;
	float intensity;

	PointLight(GameObject *obj);

	//Standard component methods
	static std::string GetTypeStatic() { return "PointLight"; }
	std::string GetType() { return GetTypeStatic(); }
	void* Get() { return this; }
};

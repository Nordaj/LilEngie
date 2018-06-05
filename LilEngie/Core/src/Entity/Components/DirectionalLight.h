#pragma once

#pragma once

#include <Entity/Component.h>
#include <Entity/GameObject.h>
#include <glm/glm.hpp>

class DirectionalLight : public Component
{
public:
	glm::vec3 dir;
	glm::vec3 color;
	float intensity;

	DirectionalLight(GameObject &obj);

	//Standard component methods
	static std::string GetTypeStatic() { return "DirectionalLight"; }
	std::string GetType() { return GetTypeStatic(); }
	void* Get() { return this; }
};

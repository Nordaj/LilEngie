#pragma once

#include <string>
#include <glm/glm.hpp>
#include <Entity/Component.h>

class Transform : public Component
{
public:
	glm::mat4 transformation;

	Transform(GameObject &obj);

	//Standard component methods
	static std::string GetTypeStatic() { return "Transform"; }
	std::string GetType() { return GetTypeStatic(); }
	void* Get() { return this; }
};

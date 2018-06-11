#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <Entity/Component.h>

class Transform : public Component
{
public:
	glm::vec3 position;
	glm::vec3 scale;
	glm::quat rotation;

	Transform(GameObject &obj);

	glm::mat4 GetModel();

	//Standard component methods
	static std::string GetTypeStatic() { return "Transform"; }
	std::string GetType() { return GetTypeStatic(); }
	void* Get() { return this; }
};

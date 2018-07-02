#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <Entity/Component.h>

class Transform : public Component
{
public:
	glm::vec3 position = { 0, 0, 0 };
	glm::vec3 scale = { 1, 1, 1 };
	glm::quat rotation = glm::quat(1, 0, 0, 0);

	Transform(GameObject *obj);

	glm::mat4 GetModel();

	COMPONENT_ID("Transform")
};

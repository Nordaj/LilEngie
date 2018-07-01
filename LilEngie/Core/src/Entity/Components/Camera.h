#pragma once

#include <glm/glm.hpp>
#include <Entity/Component.h>
#include <Entity/Components/Transform.h>
#include <Entity/GameObject.h>

class Camera : public Component
{
private:
	glm::mat4 projection;
	glm::mat4 view;
	Transform *t;

public:
	float fov;
	float near;
	float far;

	Camera(GameObject *obj);

	void SetCurrent();
	void Update();
	glm::mat4& GetProjection();
	glm::mat4& GetView();

	//Standard component methods
	static std::string GetTypeStatic() { return "Camera"; }
	std::string GetType() { return GetTypeStatic(); }
	void* Get() { return this; }
};

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
	float fov = 60;
	float near = 0.1f;
	float far = 500;

	Camera(GameObject *obj);

	void SetCurrent();
	void Update();
	glm::mat4& GetProjection();
	glm::mat4& GetView();

	COMPONENT_ID("Camera")
};

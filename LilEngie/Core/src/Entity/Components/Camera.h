#pragma once

#include <glm/glm.hpp>
#include <Entity/Component.h>
#include <Entity/GameObject.h>

class Camera : public Component
{
private:
	glm::mat4 projection;
	glm::mat4 view;

public:
	glm::vec3 position;
	glm::vec3 target;
	glm::vec3 up;
	float fov;
	float near;
	float far;

	Camera(GameObject &obj);

	void SetCurrent();
	void Update();
	glm::mat4& GetProjection();
	glm::mat4& GetView();

	//Standard component methods
	static std::string GetTypeStatic() { return "Mesh"; }
	std::string GetType() { return GetTypeStatic(); }
	void* Get() { return this; }
};

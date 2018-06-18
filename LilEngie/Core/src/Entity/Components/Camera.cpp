#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <Entity/GameObject.h>
#include <Application/Window.h>
#include <Graphics/Renderer.h>
#include <Entity/ObjectManager.h>
#include <Entity/Components/Transform.h>
#include "Camera.h"

Camera::Camera(GameObject *obj)
	:Component(obj)
{
	//Keep track of transform
	t = (Transform*) obj->GetComponent("Transform");

	fov = 60;
	near = 0.1f;
	far = 500;

	//Set myself as current if there is none
	if (Renderer::GetCurrentCamera() == nullptr)
		SetCurrent();
}

void Camera::SetCurrent()
{
	ObjectManager::SetCurrentCamera(this);
}

void Camera::Update()
{
	//Calculate view matrix
	view = glm::mat4_cast(t->rotation);
	view = glm::translate(view, -(t->position));

	//Calculate projection
	float aspect = ((float)Window::width) / ((float)Window::height);
	projection = glm::perspective(glm::radians(fov), aspect, near, far);
}

glm::mat4& Camera::GetProjection()
{
	return projection;
}

glm::mat4& Camera::GetView()
{
	return view;
}

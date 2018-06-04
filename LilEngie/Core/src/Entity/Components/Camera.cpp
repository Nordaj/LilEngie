#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Entity/GameObject.h>
#include <Application/Window.h>
#include <Graphics/Renderer.h>
#include "Camera.h"

Camera::Camera(GameObject &obj)
	:Component(obj)
{
	fov = 60;
	near = 0.1f;
	far = 500;

	position = glm::vec3(0, 0, 0);
	target = glm::vec3(0, 0, -1);
	up = glm::vec3(0, 1, 0);

	//Set myself as current if there is none
	if (Renderer::GetCurrentCamera() == nullptr)
		SetCurrent();
}

void Camera::SetCurrent()
{
	Renderer::SetCurrentCamera(this);
}

void Camera::Update()
{
	//Calculate matrices here from other properties so that i only need to do it once per frame
	view = glm::lookAt(position, target, up);

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

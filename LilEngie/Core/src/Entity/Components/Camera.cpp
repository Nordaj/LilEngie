#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <Entity/GameObject.h>
#include <Application/Window.h>
#include <Graphics/Renderer.h>
#include <Entity/SceneManager.h>
#include <Entity/Components/Transform.h>
#include "Camera.h"

Camera::Camera(GameObject *obj)
	:Component(obj)
{
	//Keep track of transform
	t = (Transform*) obj->GetComponent("Transform");

	//Set myself as current if there is none
	if (obj->GetMyScene()->GetCam() == nullptr)
		SetCurrent();
}

void Camera::SetCurrent()
{
	obj->GetMyScene()->SetCurrentCamera(this);
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

#include "Core/LilEngie.h"
#include "CameraMove.h"

CameraMove::CameraMove(GameObject *obj)
	:Component(obj)
{
	t = (Transform*)obj->GetComponent(Transform::GetTypeStatic());
}

void CameraMove::Start()
{
	if (lockMouse)
	{
		Input::lockCursorMode = true;
		Input::ShowCursor(false);
	}
}

void CameraMove::Update()
{
	//Camera look
	angles += glm::vec3(
		Input::MouseDelta().y * lookSensitivity,
		-Input::MouseDelta().x * lookSensitivity,
		0
	);
	glm::vec3 camDir = glm::vec3(
		glm::cos(angles.x) * glm::sin(angles.y),
		glm::sin(angles.x),
		glm::cos(angles.x) * glm::cos(angles.y)
	);
	glm::vec3 right = glm::vec3(
		glm::sin(angles.y - 3.14f / 2.0f),
		0,
		glm::cos(angles.y - 3.14f / 2.0f)
	);
	glm::vec3 up = glm::cross(right, camDir);
	t->rotation = glm::lookAt(t->position, t->position - camDir, up);

	//Camera movement
	if (Input::GetKey(Key::W))
		t->position += camDir * -moveSpeed * Time::deltaTime;
	else if (Input::GetKey(Key::S))
		t->position += camDir * moveSpeed * Time::deltaTime;

	if (Input::GetKey(Key::D))
		t->position += right * -moveSpeed * Time::deltaTime;
	else if (Input::GetKey(Key::A))
		t->position += right * moveSpeed * Time::deltaTime;
}

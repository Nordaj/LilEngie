#pragma once

#include "Core/LilEngie.h"

class CameraMove : public Component
{ COMPONENT_ID("CameraMove")
private:
	glm::vec3 angles;
	Transform *t;

public:
	float lookSensitivity = 1 / 360.0f;
	float moveSpeed = 2;
	bool lockMouse = true;

	CameraMove(GameObject *obj);

	void Start() override;
	void Update() override;
};

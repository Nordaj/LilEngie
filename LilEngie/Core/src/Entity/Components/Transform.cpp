#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Entity/Component.h>
#include "Transform.h"

Transform::Transform(GameObject &obj)
	:Component(obj)
{
	scale = glm::vec3(1, 1, 1);
}

glm::mat4 Transform::GetModel()
{
	glm::mat4 translationMat = glm::translate(glm::mat4(1), position);
	glm::mat4 rotationMat = glm::mat4_cast(rotation);
	glm::mat4 scaleMat = glm::scale(glm::mat4(1), scale);

	return translationMat * rotationMat * scaleMat;
}

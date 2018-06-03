#include <glm/glm.hpp>
#include <Entity/Component.h>
#include "Transform.h"

Transform::Transform(GameObject &obj)
	:Component(obj)
{
	transform = glm::mat4(1);
}

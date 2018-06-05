#include <glm/glm.hpp>
#include <Entity/GameObject.h>
#include <Entity/Component.h>
#include <Graphics/LightHandler.h>
#include "PointLight.h"

PointLight::PointLight(GameObject &obj)
	:Component(obj)
{
	//Add to lightmanager
	LightHandler::AddPointLight(this);

	//Set defaults
	color = glm::vec3(1, 1, 1);
	intensity = 1;
}

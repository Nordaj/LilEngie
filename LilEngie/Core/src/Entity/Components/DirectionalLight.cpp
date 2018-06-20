#include <glm/glm.hpp>
#include <Entity/GameObject.h>
#include <Entity/Component.h>
#include <Graphics/LightHandler.h>
#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(GameObject *obj)
	:Component(obj)
{
	//Set defaults
	color = glm::vec3(1, 1, 1);
	intensity = 1;
}

void DirectionalLight::Start()
{
	//Pass to light handler
	LightHandler::AddDirLight(this);
}

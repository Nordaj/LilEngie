#include <glm/glm.hpp>
#include <Entity/GameObject.h>
#include <Entity/Component.h>
#include <Graphics/LightHandler.h>
#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(GameObject *obj)
	:Component(obj)
{ }

void DirectionalLight::Start()
{
	//Pass to light handler
	LightHandler::AddDirLight(this);
}

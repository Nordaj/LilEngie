#include <iostream>
#include <glm/glm.hpp>
#include <Entity/GameObject.h>
#include <Entity/Component.h>
#include <Graphics/LightHandler.h>
#include "PointLight.h"

PointLight::PointLight(GameObject *obj)
	:Component(obj)
{ }

void PointLight::Start()
{
	//Add to lightmanager
	LightHandler::AddPointLight(this);
}

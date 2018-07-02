#include <Graphics/LightHandler.h>
#include <Entity/Component.h>
#include "SpotLight.h"

SpotLight::SpotLight(GameObject *obj)
	:Component(obj)
{ }

void SpotLight::Start()
{
	//Add to lightmanager
	LightHandler::AddSpotLight(this);
}

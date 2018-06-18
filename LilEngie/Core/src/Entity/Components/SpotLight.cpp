#include <Graphics/LightHandler.h>
#include <Entity/Component.h>
#include "SpotLight.h"

SpotLight::SpotLight(GameObject *obj)
	:Component(obj)
{
	//Add to lightmanager
	LightHandler::AddSpotLight(this);

	//Set defaults
	dir = glm::vec3(0, 0, -1);
	color = glm::vec3(1, 1, 1);
	intensity = 1;
	angle = glm::cos(glm::radians(10.0f)); //idk
}

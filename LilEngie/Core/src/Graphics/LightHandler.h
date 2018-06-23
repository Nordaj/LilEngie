#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <Entity/Components/PointLight.h>
#include <Entity/Components/DirectionalLight.h>
#include <Entity/Components/SpotLight.h>
#include "Shader.h"

namespace LightHandler
{
	void AddPointLight(PointLight *light);
	void AddDirLight(DirectionalLight *light);
	void AddSpotLight(SpotLight *light);
	void SetAmbient(glm::vec3 a);
	void Prepare(Shader *shader);
	void Clean();
}

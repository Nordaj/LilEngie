#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <Entity/Components/PointLight.h>
#include <Entity/Components/DirectionalLight.h>
#include <Entity/Components/SpotLight.h>
#include "Shader.h"

namespace LightHandler
{
	namespace
	{
		std::vector<PointLight*> pointLights;
		std::vector<DirectionalLight*> dirLights;
		std::vector<SpotLight*> spotLights;
		glm::vec3 ambient;
	}

	void AddPointLight(PointLight *light);
	void AddDirLight(DirectionalLight *light);
	void AddSpotLight(SpotLight *light);
	void SetAmbient(glm::vec3 a);
	void Prepare(Shader *shader);
}

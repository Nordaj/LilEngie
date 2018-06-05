#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <Entity/Components/PointLight.h>
#include <Entity/Components/DirectionalLight.h>
#include "Shader.h"

namespace LightHandler
{
	namespace
	{
		std::vector<PointLight*> pointLights;
		std::vector<DirectionalLight*> dirLights;
		glm::vec3 ambient;
	}

	void AddPointLight(PointLight *light);
	void AddDirLight(DirectionalLight *light);
	void Prepare(Shader *shader);
}

#pragma once

#include <string>
#include <vector>
#include "Core/LilEngie.h"

namespace CompConstruct
{
	//I know this is an odd way to do it, I am all ears for better ideas
	static Component *Create(std::string &name, GameObject *obj, std::vector<std::string> &params)
	{
		//Each component must be created just like the core components, on the heap
		//The GameObject class takes care of deleting the component

		///As of right now, im only using params on what i need to use them for, later i need to add choice to use params or not
		
		if (name == "Camera")
		{
			return new Camera(obj);
		}
		else if (name == "DirectionalLight")
		{
			return new DirectionalLight(obj);
		}
		else if (name == "Mesh")
		{
			Mesh *m = new Mesh(obj);
			m->Setup(params[0].c_str(), params[1].c_str());
			return m;
		}
		else if (name == "PointLight")
		{
			return new PointLight(obj);
		}
		else if (name == "SpotLight")
		{
			return new SpotLight(obj);
		}
		else if (name == "Transform")
		{
			Transform *t = new Transform(obj);

			t->position = glm::vec3(
				std::stof(params[0]), 
				std::stof(params[1]), 
				std::stof(params[2]));

			t->rotation = glm::quat(glm::vec3(
				glm::radians(std::stof(params[3])), 
				glm::radians(std::stof(params[4])), 
				glm::radians(std::stof(params[5]))));

			t->scale = glm::vec3(
				std::stof(params[6]),
				std::stof(params[7]),
				std::stof(params[8]));

			return t;
		}
	}
}

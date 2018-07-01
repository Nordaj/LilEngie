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
		//I should instead get every param with a param specifier and a value after it. then pass a hash map to interpret instead of vector
		//This way I can easily keep defaults for when theyre not specified
		//The syntax would look like:
		//Position: 0 0 0
		//Or maybe
		//Position(0, 0, 0)
		//IDK man so many options

		//I should also abstract each setup to a components static function
		
		if (name == "Camera")
		{
			//I wanted camera parameters to be optional
			if (params.size() == 0)
				return new Camera(obj);

			//In case i do have params, we can use them
			Camera *c = new Camera(obj);
			c->fov = std::stof(params[0]);
			c->near = std::stof(params[1]);
			c->far = std::stof(params[2]);
			return c;
		}
		else if (name == "DirectionalLight")
		{
			DirectionalLight *dl = new DirectionalLight(obj);

			dl->dir = glm::vec3(
				std::stof(params[0]),
				std::stof(params[1]),
				std::stof(params[2]));

			dl->color = glm::vec3(
				std::stof(params[3]),
				std::stof(params[4]),
				std::stof(params[5]));

			dl->intensity = std::stof(params[6]);

			return dl;
		}
		else if (name == "Mesh")
		{
			Mesh *m = new Mesh(obj);
			m->Setup(params[0].c_str(), params[1].c_str());
			return m;
		}
		else if (name == "PointLight")
		{
			PointLight *pl = new PointLight(obj);

			pl->pos = glm::vec3(
				std::stof(params[0]),
				std::stof(params[1]),
				std::stof(params[2]));

			pl->color = glm::vec3(
				std::stof(params[3]),
				std::stof(params[4]),
				std::stof(params[5]));

			pl->intensity = std::stof(params[6]);

			return pl;
		}
		else if (name == "SpotLight")
		{
			SpotLight *sl = new SpotLight(obj);

			sl->pos = glm::vec3(
				std::stof(params[0]),
				std::stof(params[1]),
				std::stof(params[2]));

			sl->dir = glm::vec3(
				std::stof(params[3]),
				std::stof(params[4]),
				std::stof(params[5]));

			sl->color = glm::vec3(
				std::stof(params[6]),
				std::stof(params[7]),
				std::stof(params[8]));

			sl->intensity = std::stof(params[9]);
			sl->angle = glm::cos(glm::radians(std::stof(params[10])));

			return sl;
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
		else if (name == "Text")
		{
			Text *t = new Text(obj);

			t->renderer.size = std::stof(params[0]);
			t->renderer.position = glm::vec2(
				std::stof(params[1]),
				std::stof(params[2])
			);
			t->renderer.color = glm::vec4(
				std::stof(params[3]),
				std::stof(params[4]),
				std::stof(params[5]),
				std::stof(params[6])
			);
			t->renderer.text = params[7];//This wont work like you want it to...
			t->renderer.fontName = params[8];
			t->renderer.materialName = params[9];
			t->renderer.scene = obj->GetMyScene();

			return t;
		}
	}
}

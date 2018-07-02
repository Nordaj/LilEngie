#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "Core/LilEngie.h"

namespace CompConstruct
{
	typedef std::unordered_map<std::string, std::vector<std::string>> paramMap;

	//I know this is an odd way to do it, I am all ears for better ideas
	static Component *Create(std::string &name, GameObject *obj, paramMap *params)
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
			Camera *c = new Camera(obj);

			if (params->find("Fov") != params->end())
				c->fov = std::stof((*params)["Fov"][0]);

			if (params->find("Near") != params->end())
				c->near = std::stof((*params)["Near"][0]);

			if (params->find("Far") != params->end())
				c->far = std::stof((*params)["Far"][0]);

			return c;
		}
		else if (name == "DirectionalLight")
		{
			DirectionalLight *dl = new DirectionalLight(obj);

			if (params->find("Direction") != params->end())
			{
				dl->dir = glm::vec3(
					std::stof((*params)["Direction"][0]),
					std::stof((*params)["Direction"][1]),
					std::stof((*params)["Direction"][2]));
			}

			if (params->find("Color") != params->end())
			{
				dl->color = glm::vec3(
					std::stof((*params)["Color"][0]),
					std::stof((*params)["Color"][1]),
					std::stof((*params)["Color"][2]));
			}

			if (params->find("Intensity") != params->end())
				dl->intensity = std::stof((*params)["Intensity"][0]);

			return dl;
		}
		else if (name == "Mesh")
		{
			Mesh *m = new Mesh(obj);

			//Require both model and material
			if (params->find("Model") == params->end())
				return nullptr;
			if (params->find("Material") == params->end())
				return nullptr;

			m->Setup(
				(*params)["Model"][0].c_str(), 
				(*params)["Material"][0].c_str());

			return m;
		}
		else if (name == "PointLight")
		{
			PointLight *pl = new PointLight(obj);

			if (params->find("Position") != params->end())
			{
				pl->pos = glm::vec3(
					std::stof((*params)["Position"][0]),
					std::stof((*params)["Position"][1]),
					std::stof((*params)["Position"][2]));
			}

			if (params->find("Color") != params->end())
			{
				pl->color = glm::vec3(
					std::stof((*params)["Color"][0]),
					std::stof((*params)["Color"][1]),
					std::stof((*params)["Color"][2]));
			}

			if (params->find("Intensity") != params->end())
				pl->intensity = std::stof((*params)["Intensity"][0]);

			return pl;
		}
		else if (name == "SpotLight")
		{
			SpotLight *sl = new SpotLight(obj);

			if (params->find("Position") != params->end())
			{
				sl->pos = glm::vec3(
					std::stof((*params)["Position"][0]),
					std::stof((*params)["Position"][1]),
					std::stof((*params)["Position"][2]));
			}

			if (params->find("Direction") != params->end())
			{
				sl->dir = glm::vec3(
					std::stof((*params)["Direction"][0]),
					std::stof((*params)["Direction"][1]),
					std::stof((*params)["Direction"][2]));
			}

			if (params->find("Color") != params->end())
			{
				sl->color = glm::vec3(
					std::stof((*params)["Color"][0]),
					std::stof((*params)["Color"][1]),
					std::stof((*params)["Color"][2]));
			}

			if (params->find("Intensity") != params->end())
				sl->intensity = std::stof((*params)["Intensity"][0]);

			if (params->find("Angle") != params->end())
				sl->angle = glm::cos(glm::radians(std::stof((*params)["Angle"][0])));

			return sl;
		}
		else if (name == "Transform")
		{
			Transform *t = new Transform(obj);

			if (params->find("Position") != params->end())
			{
				t->position = glm::vec3(
					std::stof((*params)["Position"][0]),
					std::stof((*params)["Position"][1]),
					std::stof((*params)["Position"][2]));
			}

			if (params->find("Rotation") != params->end())
			{
				t->rotation = glm::quat(glm::vec3(
					glm::radians(std::stof((*params)["Rotation"][0])),
					glm::radians(std::stof((*params)["Rotation"][1])),
					glm::radians(std::stof((*params)["Rotation"][2]))));
			}

			if (params->find("Scale") != params->end())
			{
				t->scale = glm::vec3(
					std::stof((*params)["Scale"][0]),
					std::stof((*params)["Scale"][1]),
					std::stof((*params)["Scale"][2]));
			}

			return t;
		}
		else if (name == "Text")
		{
			Text *t = new Text(obj);

			//Require material 
			if (params->find("Material") == params->end())
				return nullptr;

			if (params->find("Size") != params->end())
				t->renderer.size = std::stof((*params)["Size"][0]);

			if (params->find("Position") != params->end())
			{
				t->renderer.position = glm::vec2(
					std::stof((*params)["Position"][0]),
					std::stof((*params)["Position"][1])
				);
			}

			if (params->find("Color") != params->end())
			{
				t->renderer.color = glm::vec4(
					std::stof((*params)["Color"][0]),
					std::stof((*params)["Color"][1]),
					std::stof((*params)["Color"][2]),
					std::stof((*params)["Color"][3])
				);
			}

			if (params->find("Text") != params->end())
				t->renderer.text = (*params)["Text"][0];

			if (params->find("Font") != params->end())
				t->renderer.fontName = (*params)["Font"][0];

			if (params->find("Material") != params->end())
				t->renderer.materialName = (*params)["Material"][0];


			t->renderer.scene = obj->GetMyScene();

			return t;
		}
	}
}

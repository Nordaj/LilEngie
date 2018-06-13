#pragma once

#include <unordered_map>
#include <string>
#include "Model.h"

namespace ModelHandler
{
	namespace
	{
		std::unordered_map<std::string, Model> models;
	}

	Model *Get(std::string name);
	void AddModel(std::string name, Model model);
}

namespace Models = ModelHandler;

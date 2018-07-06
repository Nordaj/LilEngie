#pragma once

#include <map>
#include <string>
#include "Model.h"

class ModelHandler
{
private:
	std::map<std::string, Model*> models;

public:
	ModelHandler();
	~ModelHandler();

	Model *Get(std::string name);
	void AddModel(std::string name, Model *model);
	void Clean();
};

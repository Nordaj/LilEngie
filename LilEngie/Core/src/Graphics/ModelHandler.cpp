#include <map>
#include <string>
#include "Model.h"
#include "ModelHandler.h"

Model *ModelHandler::Get(std::string name)
{
	return &models[name];
}

void ModelHandler::AddModel(std::string name, Model model)
{
	models.insert(std::make_pair(name, model));
}

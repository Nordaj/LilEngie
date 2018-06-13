#include <string>
#include <fstream>
#include <Graphics/ModelHandler.h>
#include <Graphics/Model.h>
#include <Utilities/ModelLoader.h>
#include "SceneLoader.h"

void ReadModelCmd(std::string line)
{
	//Get parameters as string
	std::string params = line.substr(4, line.size() - 4);

	//Find first space position
	int spaceIndex = params.find(' ');

	//Take name
	std::string modelName = params.substr(0, spaceIndex);

	//Take directory
	std::string modelDir = params.substr(spaceIndex + 2, params.size() - (spaceIndex + 3));

	//Load model
	Model model = ModelLoader::Load(modelDir.c_str());

	//Add to model handler
	ModelHandler::AddModel(modelName, model);
}

bool SceneLoader::LoadScene(const char *path)
{
	std::ifstream file = std::ifstream(path);

	//Open
	if (!file.is_open())
		return false;

	//Go through lines
	std::string line;
	while (std::getline(file, line))
	{
		if (line.substr(0, 3) == "mdl")	//Model
		{
			ReadModelCmd(line);
		}
	}

	return true;
}

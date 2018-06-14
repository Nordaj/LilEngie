#include <string>
#include <fstream>
#include <Graphics/ModelHandler.h>
#include <Graphics/Model.h>
#include <Graphics/Texture.h>
#include <Graphics/TextureHandler.h>
#include <Graphics/Shader.h>
#include <Graphics/ShaderHandler.h>
#include <Utilities/ModelLoader.h>
#include "SceneLoader.h"

//TODO
///I would like to make a function that splits a line by spaces and 
///returns vector of strings instead of manually splitting myself

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

void ReadTextureCmd(std::string line)
{
	//Get parameters as string
	std::string params = line.substr(4, line.size() - 4);

	//Find first space index
	int spaceIndex = params.find(' ');

	//Take name
	std::string texName = params.substr(0, spaceIndex);

	//Take directory
	std::string texDir = params.substr(spaceIndex + 2, params.size() - (spaceIndex + 3));

	//Create texture
	Texture tex = Texture(texDir.c_str());

	//Add texture to handler
	TextureHandler::AddTex(texName, tex);
}

void ReadShaderCmd(std::string line)
{
	//Get parameters as string
	std::string params = line.substr(4, line.size() - 4);

	//Find first space index
	int spaceIndex = params.find(' ');

	//take name
	std::string shaderName = params.substr(0, spaceIndex);

	//Take directory
	std::string shaderDir = params.substr(spaceIndex + 2, params.size() - (spaceIndex + 3));

	//Add to shaders
	Shaders::Create(shaderName, shaderDir.c_str());
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
		else if (line.substr(0, 3) == "tex") //Texture
		{
			ReadTextureCmd(line);
		}
		else if (line.substr(0, 3) == "shd") //Shader
		{
			ReadShaderCmd(line);
		}
	}

	return true;
}

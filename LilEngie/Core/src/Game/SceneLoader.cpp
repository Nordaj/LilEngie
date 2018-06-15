#include <string>
#include <fstream>
#include <vector>
#include <Graphics/ModelHandler.h>
#include <Graphics/Model.h>
#include <Graphics/Texture.h>
#include <Graphics/TextureHandler.h>
#include <Graphics/Shader.h>
#include <Graphics/ShaderHandler.h>
#include <Graphics/Material.h>
#include <Graphics/MaterialHandler.h>
#include <Utilities/ModelLoader.h>
#include "SceneLoader.h"

//I'm lazy... dont judge me
typedef std::vector<std::string> sVec;

std::vector<std::string> Split(std::string &ref, char refChar)
{
	std::vector<std::string> val;

	//Store remaining params as i cycle through
	std::string remaining = ref;

	//Loop through each param
	for (;;)
	{
		//Get index of char
		int index = remaining.find(refChar);

		//Check if done
		if (index == std::string::npos)
		{
			if (remaining.size() > 0)
				index = remaining.size();
			else
				break;
		}

		//Get it into string
		std::string param = remaining.substr(0, index);

		//Add to vector
		val.push_back(param);

		//Remove from remaining
		remaining.erase(0, index + 1);
	}

	return val;
}

void Erase(std::string &ref, char c)
{
	for (;;)
	{
		//Get index to remove if necessary
		int index = ref.find(c);
		if (index == std::string::npos)
			break;

		ref.erase(index, 1);
	}
}

void ReadModelCmd(std::string &line)
{
	//Filter command parameters
	sVec splits = Split(line, ' ');
	Erase(splits[2], '"');

	//Setup model
	Model model = ModelLoader::Load(splits[2].c_str());
	Models::AddModel(splits[1], model);
}

void ReadTextureCmd(std::string &line)
{
	//Filter command parameters
	sVec splits = Split(line, ' ');
	Erase(splits[2], '"');

	//Setup texture
	Texture tex = Texture(splits[2].c_str());
	Textures::AddTex(splits[1], tex);
}

void ReadShaderCmd(std::string &line)
{
	//Filter command parameters
	sVec splits = Split(line, ' ');
	Erase(splits[2], '"');

	//Add to shaders
	Shaders::Create(splits[1], splits[2].c_str());
}

void ReadMaterialCmd(std::string &line)
{
	//Filter command parameters
	sVec splits = Split(line, ' ');

	//Create material
	MaterialHandler::Add(splits[1], splits[2]);
}

void UseMaterialDash(std::string &line, std::string &passed)
{
	//Get material name
	std::string matName = Split(passed, ' ')[1];

	//Filter command parameters
	sVec splits = Split(line, ' ');

	//Remove quotes
	Erase(splits[1], '"');

	//Add correct uniform looking at type
	if (splits[0] == "-col")
	{
		Mats::Get(matName)->AddColor(
			splits[1].c_str(), 
			std::stof(splits[2]), 
			std::stof(splits[3]),
			std::stof(splits[4]), 
			std::stof(splits[5]));
	}
	else if (splits[0] == "-tex")
	{
		Mats::Get(matName)->AddTexture(
			splits[1].c_str(), 
			*Textures::Get(splits[2]));
	}
	else if (splits[0] == "-flt")
	{
		Mats::Get(matName)->AddFloat(
			splits[1].c_str(), 
			std::stof(splits[2]));
	}
	else if (splits[0] == "-int")
	{
		Mats::Get(matName)->AddInt(
			splits[1].c_str(), 
			std::stoi(splits[2]));
	}
}

bool SceneLoader::LoadScene(const char *path)
{
	//Open file
	std::ifstream file = std::ifstream(path);
	if (!file.is_open())
		return false;

	//Keep track of commands that have -'s after the line
	std::string passedLine;

	//Go through lines
	std::string line;
	while (std::getline(file, line))
	{
		if (line.substr(0, 3) == "mdl")			//Model
		{
			ReadModelCmd(line);
		}
		else if (line.substr(0, 3) == "tex")	//Texture
		{
			ReadTextureCmd(line);
		}
		else if (line.substr(0, 3) == "shd")	//Shader
		{
			ReadShaderCmd(line);
		}
		else if (line.substr(0, 3) == "mat")	//Material
		{
			passedLine = line;
			ReadMaterialCmd(line);
		}
		else if (line.substr(0, 3) == "obj")
		{
			//TODO (IDK HOW)
		}
		else if (line[0] == '-')
		{
			if (passedLine.substr(0, 3) == "mat")		//Material param
				UseMaterialDash(line, passedLine);
			else if (passedLine.substr(0, 3) == "obj")	//Object param
			{ }
		}
	}

	return true;
}

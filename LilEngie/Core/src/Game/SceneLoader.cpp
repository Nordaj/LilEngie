#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <Graphics/ModelHandler.h>
#include <Graphics/Model.h>
#include <Graphics/Texture.h>
#include <Graphics/TextureHandler.h>
#include <Graphics/Shader.h>
#include <Graphics/ShaderHandler.h>
#include <Graphics/Material.h>
#include <Graphics/MaterialHandler.h>
#include <Utilities/ModelLoader.h>
#include <Entity/Scene.h>
#include "../../ComponentConstruction.h"
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

std::vector<std::string> SplitParams(std::string &ref)
{
	bool inParam = false;
	int prev = -1;
	std::string rem = ref; //Stores remaining
	sVec params;

	for (int i = 0; i < ref.size(); i++)
	{
		//Keep track of whether im in a param
		if (rem[i] == '(')
			inParam = true;
		else if (rem[i] == ')')
			inParam = false;

		//Split if im a space
		if ((rem[i] == ' ' || i == rem.size() - 1) && !inParam)
		{
			std::string param = rem.substr(prev + 1, i + 1 - (prev + 1));
			prev = i;

			//Remove space if its there
			if (param[param.size() - 1] == ' ')
				param.erase(param.size() - 1, 1);

			params.push_back(param);
		}
	}

	if (inParam)
		ERROR(("You have a problem with your parenthesis: \n" + ref).c_str());

	return params;
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

void GetNamesNValues(sVec *names, sVec *values, sVec &splits)
{
	for (int i = 0; i < splits.size(); i++)
	{
		int index = splits[i].find('(');
		std::string name = splits[i].substr(0, index);
		std::string vals = splits[i].substr(index + 1, splits[i].size() - (index + 2));
		names->push_back(name);
		values->push_back(vals);
	}
}

void ReadModelCmd(std::string &line, Scene *scene)
{
	//Filter command parameters
	sVec splits = Split(line, ' ');
	Erase(splits[2], '"');

	//Setup model TODO
	Model *model = ModelLoader::Load(splits[2].c_str());
	scene->models.AddModel(splits[1], model);
}

void ReadTextureCmd(std::string &line, Scene *scene)
{
	//Filter command parameters
	sVec splits = Split(line, ' ');
	Erase(splits[2], '"');

	//Setup texture
	Texture tex = Texture(splits[2].c_str());
	scene->textures.AddTex(splits[1], tex);
}

void ReadShaderCmd(std::string &line, Scene *scene)
{
	//Filter command parameters
	sVec splits = Split(line, ' ');
	Erase(splits[2], '"');

	//Add to shaders
	scene->shaders.Create(splits[1], splits[2].c_str());
}

void ReadMaterialCmd(std::string &line, Scene *scene)
{
	//Filter command parameters
	sVec splits = Split(line, ' ');

	//Create material
	scene->materials.Add(splits[1], splits[2], &scene->shaders);
}

void ReadObjectCmd(std::string &line, Scene *scene)
{
	//Filter command parameters
	sVec splits = Split(line, ' ');

	//Add to current scene
	scene->AddObject(splits[1]);
}

void UseMaterialDash(std::string &line, std::string &passed, Scene *scene)
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
		scene->materials.Get(matName)->AddColor(
			splits[1].c_str(), 
			std::stof(splits[2]), 
			std::stof(splits[3]),
			std::stof(splits[4]), 
			std::stof(splits[5]));
	}
	else if (splits[0] == "-tex")
	{
		scene->materials.Get(matName)->AddTexture(
			splits[1].c_str(), 
			*scene->textures.Get(splits[2]));
	}
	else if (splits[0] == "-flt")
	{
		scene->materials.Get(matName)->AddFloat(
			splits[1].c_str(), 
			std::stof(splits[2]));
	}
	else if (splits[0] == "-int")
	{
		scene->materials.Get(matName)->AddInt(
			splits[1].c_str(), 
			std::stoi(splits[2]));
	}
}

void UseObjectDash(std::string &line, std::string &passed, Scene *scene)
{
	//Get last obj string
	std::string last = Split(passed, ' ')[1];

	//Split up parameters
	sVec splits = SplitParams(line);
	std::string type = splits[0];
	Erase(type, '-');
	splits.erase(splits.begin());

	//Split param names and values
	sVec names;
	sVec values;
	GetNamesNValues(&names, &values, splits);

	//Add stuff to map
	std::unordered_map<std::string, sVec> parameters;
	for (int i = 0; i < names.size(); i++)
	{
		sVec vals = Split(values[i], ',');
		parameters.insert(std::make_pair(names[i], vals));
	}

	//Call component listing
	void *t = CompConstruct::Create(type, scene->GetObject(last), &parameters);

	//Error handling (not great but can hopefully kinda work for now)
	if (t == nullptr)
		ERROR(("Could not create component with: \n" + line).c_str());
}

void SceneLoader::LoadScene(const char *path, Scene *scene)
{
	//Construct scene
	//scene = new Scene();

	//Open file
	std::ifstream file = std::ifstream(path);
	if (!file.is_open())
		ERROR(((std::string)"Could not load .lilscn file with the path:\n" + path).c_str());

	//Keep track of commands that have -'s after the line
	std::string passedLine;

	//Go through lines
	std::string line;
	while (std::getline(file, line))
	{
		if (line.substr(0, 2) == "//")			//Comment
		{
			continue;
		}
		else if (line == "")					//White line
		{
			continue;
		}
		if (line.substr(0, 3) == "mdl")			//Model
		{
			ReadModelCmd(line, scene);
		}
		else if (line.substr(0, 3) == "tex")	//Texture
		{
			ReadTextureCmd(line, scene);
		}
		else if (line.substr(0, 3) == "shd")	//Shader
		{
			ReadShaderCmd(line, scene);
		}
		else if (line.substr(0, 3) == "mat")	//Material
		{
			passedLine = line;
			ReadMaterialCmd(line, scene);
		}
		else if (line.substr(0, 3) == "obj")	//Object
		{
			passedLine = line;
			ReadObjectCmd(line, scene);
		}
		else if (line[0] == '-')
		{
			//Decide parameter type
			if (passedLine.substr(0, 3) == "mat")		
				UseMaterialDash(line, passedLine, scene);
			else if (passedLine.substr(0, 3) == "obj")	
				UseObjectDash(line, passedLine, scene);
		}
		else if (line.substr(0, 3) == "amb")	//Ambient color
		{
			sVec params = Split(line, ' ');
			scene->ambient = glm::vec3(
				std::stof(params[1]),
				std::stof(params[2]),
				std::stof(params[3])
			);
		}
		else if (line.substr(0, 3) == "clr")	//Clear color
		{
			sVec params = Split(line, ' ');
			scene->clearColor = glm::vec3(
				std::stof(params[1]),
				std::stof(params[2]),
				std::stof(params[3])
			);
		}
		else									//Not a valid command type
		{
			ERROR(("Invalid command type: \n" + line).c_str());
		}
	}

	//Set scene as loaded
	scene->isLoaded = true;
}

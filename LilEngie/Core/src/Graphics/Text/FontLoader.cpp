#include <fstream>
#include <vector>
#include <string>
#include "FontLoader.h"

namespace FontLoader
{
	//Single out spaces, no repeats
	void SpaceErase(std::string *line)
	{
		for (int i = 0; i < line->size(); i++)
		{
			if ((*line)[i] == ' ')
			{
				if ((*line)[i + 1] == ' ')
					line->erase(i, 1);
			}
		}
	}

	//Clear out all chars that are not numbers
	void NumOnly(std::string *line)
	{
		for (int i = 0; i < line->size(); i++)
		{
			if ((line[0][i] < '0' || line[0][0] > '9') && line[0][i] != '-' && line[0][i] != '.')
				line->erase(i, 1);
		}
	}

	//Split into vector by char
	std::vector<std::string> Split(std::string &line, char refChar)
	{
		std::vector<std::string> val;

		//Store remaining params as i cycle through
		std::string remaining = line;

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

	//Asign values to character instance
	Character SetupChar(std::vector<std::string> &numbers)
	{
		Character c = Character();
		c.posX = std::stoi(numbers[1]);
		c.posY = std::stoi(numbers[2]);
		c.width = std::stoi(numbers[3]);
		c.height = std::stoi(numbers[4]);
		c.offsetX = std::stoi(numbers[5]);
		c.offsetY = std::stoi(numbers[6]);
		c.advance = std::stoi(numbers[7]);
		return c;
	}
}

int FontLoader::Load(const char *path, CharMap *map)
{
	//Open file
	std::ifstream file = std::ifstream(path);
	if (!file.is_open())
		return 1;

	//Iterate through lines
	std::string line;
	while (std::getline(file, line))
	{
		//Check if char line
		if (line.substr(0, 5) == "char ")
		{
			//Filter through stuff till i get character
			SpaceErase(&line);
			NumOnly(&line);
			std::vector<std::string> params = Split(line, ' ');
			Character character = SetupChar(params);

			//Add to charmap, using ID[0] to get char 
			char c = std::stoi(params[0]);
			map->insert(std::make_pair(c, character));
		}
	}

	return 0;
}

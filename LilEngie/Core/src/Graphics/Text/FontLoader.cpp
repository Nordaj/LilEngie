#include <fstream>
#include <vector>
#include <string>
#include "FontLoader.h"

namespace FontLoader
{
	//Single out spaces, no repeats
	void SpaceErase(std::string *line)
	{
		//Erase any double instances of space
		for (int i = 0; i < line->size(); i++)
		{
			if ((*line)[i] == ' ')
			{
				if ((*line)[i + 1] == ' ')
				{
					line->erase(i, 1);
					
					//Prevent from skipping char after erase
					i--;
				}
			}
		}
	}

	//Clear out all chars that are not numbers
	void NumOnly(std::string *line)
	{
		//Setup copy
		std::string cpy = *line;

		for (int i = 0; i < cpy.size(); i++)
		{
			if ((cpy[i] < '0' || cpy[i] > '9') && cpy[i] != '-' && cpy[i] != '.' && cpy[i] != ' ')
			{
				cpy.erase(i, 1);
				i--;
			}
		}

		//Assign value
		*line = cpy;
	}

	//Split into vector by char
	std::vector<std::string> Split(std::string &line, char refChar)
	{
		std::vector<std::string> val;

		//Store remaining params as i cycle through
		std::string remaining = line;

		//Remove spaces in front/back
		if (remaining[0] == ' ')
			remaining.erase(0, 1);
		if (remaining[remaining.size()] == ' ')
			remaining.erase(remaining.size(), 1);

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

int FontLoader::Load(const char *path, CharMap *map, std::string *texName)
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
		//Check if its that line that tells me where my texture is
		else if (line.substr(0, 4) == "page")
		{
			//Get the file name from that line that tells me the file name
			int index = line.find('"');
			std::string textureName = line.substr(index + 1, line.size() - index);
			textureName.erase(textureName.size() - 1, 1);

			//Copy path param to string and erase file name
			std::string p = path;
			int finalSlash = p.find_last_of('/');
			p.erase(finalSlash + 1, p.size() - finalSlash + 1);

			//Append strings
			textureName = p + textureName;

			//Assign
			(*texName) = textureName;
		}
	}

	return 0;
}

#include <string>
#include <fstream>
#include <vector>

#include "ModelLoader.h"

int ModelLoader::LoadOBJ(const char* path, std::vector<float> *verts, std::vector<unsigned int> *inds)
{
	//Create file stream
	std::ifstream file = std::ifstream(path);

	//Check if we have a file
	if (file.is_open())
	{
		//Go through file line by line
		std::string line;
		while (std::getline(file, line))
		{
			if (line[0] == 'v')
			{
				//String used to store unevaluated numbers
				std::string numbers = line.substr(2, line.size() - 2);

				//Go through each number
				for (;;)
				{
					//Get index of next space
					int spaceIndex = numbers.find(' ');

					//If no spaces left, set it to size
					if (spaceIndex == std::string::npos)
						spaceIndex = numbers.size() - 1;

					//Break if the size is 0, means im done
					if (numbers.size() == 0)
						break;

					//Add value to verts
					verts->push_back(std::stof(numbers.substr(0, spaceIndex)));

					//Remove evaluated number from numbers
					numbers = numbers.substr(spaceIndex + 1, numbers.size() - spaceIndex - 1);
				}
			}
			else if (line[0] == 'f')
			{
				//String used to store unevaluated numbers
				std::string numbers = line.substr(2, line.size() - 2);

				//Go through each number
				for (;;)
				{
					//Get index of next space
					int spaceIndex = numbers.find(' ');

					//If no spaces left, set it to size
					if (spaceIndex == std::string::npos)
						spaceIndex = numbers.size() - 1;

					//Break if the size is 0, means im done
					if (numbers.size() == 0)
						break;

					//Add value to verts
					inds->push_back(std::stoi(numbers.substr(0, spaceIndex + 1)) - 1);

					//Remove evaluated number from numbers
					numbers = numbers.substr(spaceIndex + 1, numbers.size() - spaceIndex - 1);
				}
			}
		}
	}
	else
	{
		return 1;
	}
}

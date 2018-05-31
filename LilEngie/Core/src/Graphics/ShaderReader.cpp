#include <string>
#include <fstream>

#include "ShaderReader.h"

void ShaderReader::ReadShader(std::string *vertex, std::string *surface, std::string path)
{
	//Create ifstream
	std::ifstream file = std::ifstream(path);

	//Use to keep track
	int currentType = 0; //0=undef, 1=vert, 2=surf

	//Go through stream
	std::string line;
	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			//Check shader type
			if (line == "#vert")
			{
				currentType = 1;
				continue;
			}
			else if (line == "#surf")
			{
				currentType = 2;
				continue;
			}

			//Append current line
			if (currentType == 1)
				vertex->append(line).append("\n");
			else if (currentType == 2)
				surface->append(line).append("\n");
		}
	}
}

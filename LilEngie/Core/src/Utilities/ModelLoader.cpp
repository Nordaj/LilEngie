#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <Application/Debug.h>
#include <Graphics/Vertex.h>
#include "ModelLoader.h"

//DO NOT USE, UNDER WORK
int ModelLoader::LoadOBJManual(const char* path, std::vector<float> *verts,  std::vector<unsigned int> *inds)
{
	//=====CURRENTLY BROKEN=====//

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
			else if (line.substr(0, 2) == "vn")
			{
				
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

Model *ModelLoader::Load(const char* path)
{
	//Load into importer
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_CalcTangentSpace);

	//Check for problems
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		LOG("Could not load mesh");

	//Get aimesh, just get the first mesh of loaded file. I don't care about loading multiple obj's rn
	aiMesh *mesh = scene->mMeshes[0];

	//Model to return
	Model *model = new Model();

	//Get verts
	for (int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex v;

		//Positions
		v.position.x = mesh->mVertices[i].x;
		v.position.y = mesh->mVertices[i].y;
		v.position.z = mesh->mVertices[i].z;

		//Tex coords
		if (mesh->mTextureCoords[0]) 
		{
			v.uv.x = mesh->mTextureCoords[0][i].x;
			v.uv.y = mesh->mTextureCoords[0][i].y;
		}

		//Normals (Should always exist)
		v.normal.x = mesh->mNormals[i].x;
		v.normal.y = mesh->mNormals[i].y;
		v.normal.z = mesh->mNormals[i].z;

		//Tangents (Should always exist)
		v.tangent.x = mesh->mTangents[i].x;
		v.tangent.y = mesh->mTangents[i].y;
		v.tangent.z = mesh->mTangents[i].z;

		//Push vert
		model->vertices.push_back(v);
	}

	//Get inds
	for (int i = 0; i < mesh->mNumFaces; i++)
	{
		//Now i need to sort through indices per face
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			model->indices.push_back(face.mIndices[j]);
		}
	}

	//Return
	return model;
}

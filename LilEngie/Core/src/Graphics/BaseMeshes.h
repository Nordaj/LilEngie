#pragma once

#include <vector>

namespace BaseMeshes
{
	//==========TRIANGLE==========//
	std::vector<float> triangleVerts = {
		 0.0f,  0.5f,  0.0f, //0
		 0.5f, -0.5f,  0.0f, //1
		-0.5f, -0.5f,  0.0f, //3
	};

	std::vector<unsigned int> triangleInd = {
		0, 1, 2
	};
	//==========TRIANGLE==========//
}
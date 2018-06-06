#pragma once

#include <vector>

class Model
{
public:
	std::vector<float> vertices;
	std::vector<unsigned int> indices;

	Model();
	void Setup(std::vector<float> &verts, std::vector<unsigned int> &inds);
};

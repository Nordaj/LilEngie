#pragma once

#include <vector>

class Model
{
public:
	std::vector<float> vertices;
	std::vector<unsigned int> indices;

	Model();
	Model(std::vector<float> &verts, std::vector<unsigned int> &inds);
	Model(std::vector<float> verts, std::vector<unsigned int> inds);
	void Setup(std::vector<float> &verts, std::vector<unsigned int> &inds);
};

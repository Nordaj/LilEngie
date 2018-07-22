#pragma once

#include <vector>
#include "Vertex.h"

class Model
{
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	Model();
	Model(std::vector<Vertex> &verts, std::vector<unsigned int> &inds);
	Model(std::vector<Vertex> verts, std::vector<unsigned int> inds);
	void Setup(std::vector<Vertex> &verts, std::vector<unsigned int> &inds);
};

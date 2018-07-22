#include <vector>
#include "Model.h"

Model::Model()
{ }

Model::Model(std::vector<Vertex> &verts, std::vector<unsigned int> &inds)
{
	vertices = verts;
	indices = inds;
}

Model::Model(std::vector<Vertex> verts, std::vector<unsigned int> inds)
{
	vertices = verts;
	indices = inds;
}

void Model::Setup(std::vector<Vertex> &verts, std::vector<unsigned int> &inds)
{
	vertices = verts;
	indices = inds;
}

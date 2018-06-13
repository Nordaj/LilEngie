#include <vector>
#include "Model.h"

Model::Model()
{ }

Model::Model(std::vector<float> verts, std::vector<unsigned int> inds)
{
	vertices = verts;
	indices = inds;
}

void Model::Setup(std::vector<float> &verts, std::vector<unsigned int> &inds)
{
	vertices = verts;
	indices = inds;
}

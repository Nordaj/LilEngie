#include <vector>
#include "Model.h"

Model::Model()
{ }

void Model::Setup(std::vector<float> &verts, std::vector<unsigned int> &inds)
{
	vertices = verts;
	indices = inds;
}

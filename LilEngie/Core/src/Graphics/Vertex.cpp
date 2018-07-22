#include <vector>
#include "Vertex.h"

std::vector<float> Vertex::ToFloatVec(std::vector<Vertex> &verts)
{
	//Create float vector of right size
	std::vector<float> fVec = std::vector<float>(verts.size() * 11);

	//Copy data from vert vector to float vector
	memcpy(&fVec[0], &verts[0], verts.size() * 11 * sizeof(float));

	return fVec;
}

std::vector<Vertex> Vertex::ToVertVec(std::vector<float> &verts)
{
	//Make sure stuff will fit
	if (verts.size() % 11 != 0)
		return std::vector<Vertex>();

	//Create vert vector of right size
	std::vector<Vertex> vVec = std::vector<Vertex>(verts.size() / 11);

	//Copy data over
	memcpy(&vVec[0], &verts[0], (verts.size() / 11) * sizeof(float));
}

#pragma once

#include <vector>

namespace ModelLoader
{
	int LoadOBJ(const char* path, std::vector<float> *verts, std::vector<unsigned int> *inds);
}

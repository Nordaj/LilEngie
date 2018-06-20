#pragma once

#include <vector>
#include <Graphics/Model.h>

namespace ModelLoader
{
	int LoadOBJManual(const char* path, std::vector<float> *verts, std::vector<unsigned int> *inds);
	Model *Load(const char* path);
}

#include <map>
#include <string>
#include "BaseMeshes.h"
#include "Model.h"
#include "ModelHandler.h"

ModelHandler::ModelHandler()
{
	//Add base meshes to array here
	Model *cube = new Model();
	cube->vertices = BaseMeshes::cube.vertices;
	cube->indices = BaseMeshes::cube.indices;
	AddModel("BaseCube", cube);

	Model *quad = new Model();
	quad->vertices = BaseMeshes::quad.vertices;
	quad->indices = BaseMeshes::quad.indices;
	AddModel("BaseQuad", quad);
}

ModelHandler::~ModelHandler()
{
	//Deallocate everything
	std::map<std::string, Model*>::iterator it;
	for (it = models.begin(); it != models.end(); it++)
		delete it->second;
}

Model *ModelHandler::Get(std::string name)
{
	return models[name];
}

void ModelHandler::AddModel(std::string name, Model *model)
{
	models.insert(std::make_pair(name, model));
}

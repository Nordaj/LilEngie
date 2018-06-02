#include <iostream>
#include <string>

#include "Core/LilEngie.h"

int main()
{
	Game::Init();

	//Create unlit shader
	int unlitShader = ShaderHandler::AddShader("Resources/Unlit.shader");

	//Create blue green material
	int blueMat = MaterialHandler::CreateMaterial(unlitShader);
	MaterialHandler::GetMaterial(blueMat)->AddColor("uColor", 0, 1, 1, 1);

	//Create red material
	int redMat = MaterialHandler::CreateMaterial(unlitShader);
	MaterialHandler::GetMaterial(redMat)->AddColor("uColor", 1, 0, 0, 1);

	//-----OBJECT ONE-----//
	///Create object 
	GameObject obj = GameObject();
	ObjectManager::AddObject(obj);

	///Add transform
	Transform tran = Transform(obj);
	obj.AddComponent(tran);

	///Add mesh
	Mesh mesh = Mesh(obj);
	obj.AddComponent(mesh);

	///Setup mesh
	mesh.Setup(BaseMeshes::triangleVerts, BaseMeshes::triangleInd, blueMat);

	///Move transform
	tran.transformation = glm::translate(tran.transformation, glm::vec3(0.5f, 0, 0));

	//-----OBJECT TWO-----//
	///Create object
	GameObject left = GameObject();
	ObjectManager::AddObject(left);

	///Add transform
	Transform leftTran = Transform(left);
	left.AddComponent(leftTran);

	///Add mesh
	Mesh leftMesh = Mesh(left);
	left.AddComponent(leftMesh);

	///Setup mesh
	leftMesh.Setup(BaseMeshes::triangleVerts, BaseMeshes::triangleInd, redMat);

	///Move transform
	leftTran.transformation = glm::translate(leftTran.transformation, glm::vec3(-0.5f, 0.2f, 0));

	Game::Run();
	Game::Close();

	return 0;
}

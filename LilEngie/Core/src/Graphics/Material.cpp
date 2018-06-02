#include <string>
#include <glm/glm.hpp>
#include "UniformHandler.h"
#include "Shader.h"
#include "Material.h"

Material::Material(Shader *s)
	:shader(s)
{ }

void Material::Prepare(glm::mat4 &mvp)
{
	shader->SetCurrent();
	UniformHandler::PassMat4(shader->GetID(), (char*)"uMVPMat", mvp);

	//Isn't a very DRY method, ill have to figure out other ways later

	//Pass all textures
	std::map<unsigned int, unsigned int>::iterator texIt;
	for (texIt = textures.begin(); texIt != textures.end(); texIt++)
		UniformHandler::PassTexture(texIt->first, texIt->second);

	//Pass all colors
	std::map<std::string, glm::vec4>::iterator colIt;
	for (colIt = colors.begin(); colIt != colors.end(); colIt++)
		UniformHandler::PassVec4(shader->GetID(), (char*)colIt->first.c_str(), colIt->second);

	//Pass all floats
	std::map<std::string, float>::iterator fIt;
	for (fIt = floats.begin(); fIt != floats.end(); fIt++)
		UniformHandler::PassFloat(shader->GetID(), (char*)fIt->first.c_str(), fIt->second);

	//Pass all ints
	std::map<std::string, int>::iterator intIt;
	for (intIt = integers.begin(); intIt != integers.end(); intIt++)
		UniformHandler::PassInt(shader->GetID(), (char*)intIt->first.c_str(), intIt->second);
}

void Material::AddTexture(unsigned int texUnit, unsigned int texture)
{
	textures.insert(std::make_pair(texUnit, texture));
}

void Material::AddColor(const char* uniform, float r, float g, float b, float a)
{
	colors.insert(std::make_pair(uniform, glm::vec4(r, g, b, a)));
}

void Material::AddFloat(const char* uniform, float val)
{
	floats.insert(std::make_pair(uniform, val));
}

void Material::AddInt(const char* uniform, int val)
{
	floats.insert(std::make_pair(uniform, val));
}

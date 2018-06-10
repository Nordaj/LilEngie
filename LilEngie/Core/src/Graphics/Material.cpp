#include <map>
#include <string>
#include <glm/glm.hpp>
#include "UniformHandler.h"
#include "ShaderHandler.h"
#include "Shader.h"
#include "Texture.h"
#include "Material.h"

Material::Material(int shader)
	:shader(shader)
{ }

void Material::Prepare(glm::mat4 &mvp, glm::mat4 &model)
{
	//Set shader stuff
	ShaderHandler::SetShader(shader);

	//Get shader
	Shader *s = ShaderHandler::Get(shader);

	//Pass uniforms
	UniformHandler::PassMat4(s->GetID(), "uMVPMat", mvp);
	UniformHandler::PassMat4(s->GetID(), "uModelMat", model);

	//Isn't a very DRY method, ill have to figure out other ways later

	//Pass all textures (a bit more complex than the rest)
	std::map<std::string, Texture>::iterator texIt;
	int i = 0;
	for (texIt = textures.begin(); texIt != textures.end(); texIt++)
	{
		UniformHandler::PassTexture(s->GetID(), texIt->first.c_str(), i, texIt->second.GetID());
		i++;
	}

	//Pass all colors
	std::map<std::string, glm::vec4>::iterator colIt;
	for (colIt = colors.begin(); colIt != colors.end(); colIt++)
		UniformHandler::PassVec4(s->GetID(), colIt->first.c_str(), colIt->second);

	//Pass all floats
	std::map<std::string, float>::iterator fIt;
	for (fIt = floats.begin(); fIt != floats.end(); fIt++)
		UniformHandler::PassFloat(s->GetID(), fIt->first.c_str(), fIt->second);

	//Pass all ints
	std::map<std::string, int>::iterator intIt;
	for (intIt = integers.begin(); intIt != integers.end(); intIt++)
		UniformHandler::PassInt(s->GetID(), intIt->first.c_str(), intIt->second);
}

Shader* Material::GetShader()
{
	return ShaderHandler::Get(shader);
}

void Material::AddTexture(const char *uniform, Texture texture)
{
	textures.insert(std::make_pair(uniform, texture));
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

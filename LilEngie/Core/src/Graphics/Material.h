#pragma once

#include <string>
#include <map>
#include <glm/glm.hpp>
#include "Shader.h"

class Material
{
private:
	Shader *shader;

	//First is the texture unit(eg GL_TEXTURE0). the second is the texture ID
	std::map<unsigned int, unsigned int> textures;

	//First is uniform name. second is value to be passed
	std::map<std::string, glm::vec4> colors;
	std::map<std::string, float> floats;
	std::map<std::string, int> integers;

public:
	Material(Shader *s);

	//Function to bind current shader and pass all uniforms
	void Prepare(glm::mat4 &mvp);

	void AddTexture(unsigned int texUnit, unsigned int texture);
	void AddColor(const char* uniform, float r, float g, float b, float a);
	void AddFloat(const char* uniform, float val);
	void AddInt(const char* uniform, int val);
};

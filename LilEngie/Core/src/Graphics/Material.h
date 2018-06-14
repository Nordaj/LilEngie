#pragma once

#include <string>
#include <map>
#include <vector>
#include <glm/glm.hpp>
#include "Texture.h"
#include "Shader.h"

class Material
{
private:
	std::string shader;

	//First is uniform name. second is value to be passed
	std::map<std::string, Texture> textures;
	std::map<std::string, glm::vec4> colors;
	std::map<std::string, float> floats;
	std::map<std::string, int> integers;

public:
	Material(std::string shader);

	//Function to bind current shader and pass all uniforms
	void Prepare(glm::mat4 &mvp, glm::mat4 &model);
	Shader* GetShader();

	void AddTexture(const char *uniform, Texture texture);
	void AddColor(const char* uniform, float r, float g, float b, float a);
	void AddFloat(const char* uniform, float val);
	void AddInt(const char* uniform, int val);
};

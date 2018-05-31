#pragma once

#include <string>

//SHADER RULES
///Use #vert to define vertex shader
///Use #surf to define surface shader
///Shader extension is a choice but use .shader for consistency

namespace ShaderReader
{
	void ReadShader(std::string *vertex, std::string *surface, std::string path);
}

#pragma once

#include <string>
#include <glm/glm.hpp>
#include <Entity/Component.h>
#include <Graphics/Text/TextRenderer.h>

class Text : public Component
{
public:
	TextRenderer renderer;

	Text(GameObject *obj);

	//Standard component methods
	static std::string GetTypeStatic() { return "Text"; } 
	std::string GetType() { return GetTypeStatic(); }
	void* Get() { return this; }
};

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

	COMPONENT_ID("Text")
};

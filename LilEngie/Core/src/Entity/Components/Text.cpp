#include "Text.h"

#include <Graphics/Text/TextHandler.h>
#include <Graphics/Text/TextRenderer.h>

Text::Text(GameObject *obj)
	:Component(obj)
{ 
	TextHandler::texts.push_back(&renderer);
}

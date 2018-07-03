#include <Graphics/Text/TextHandler.h>
#include <Graphics/Text/TextRenderer.h>
#include <Entity/GameObject.h>
#include "Text.h"

Text::Text(GameObject *obj)
	:Component(obj)
{ 
	obj->GetMyScene()->texts.texts.push_back(&renderer);
}

#include <Graphics/Texture.h>
#include "Font.h"

void Font::SetupTexture(const char *path)
{
	//I'll just use the texture's loading even though 
	//im not storing it as a texture. dont judge me
	Texture t = Texture(path, true, true, &width, &height);
	texID = t.GetID();
}
#include <iostream>
#include <stb_image.h>
#include <Platform/Gfx.h>
#include <Application/Debug.h>
#include "Texture.h"

Texture::Texture(const char *path, bool repeat, bool filter, int *width, int *height)
{
	//Setup variables
	int locWidth, locHeight;
	int *widthPtr, *heightPtr;
	int channels = 1; //Assume 1

	//Assign width and heights depending on if im using params
	if (width != nullptr) widthPtr = width;
	else widthPtr = &locWidth;
	if (height != nullptr) heightPtr = height;
	else heightPtr = &locHeight;

	//Load texture
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(path, widthPtr, heightPtr, &channels, 0);

	//Check for problems (not even sure if it returns nullptr on fail)
	if (data == nullptr)
		LOG("Could not load texture");

	//Submit stuff to gpu
	tex = Gfx::CreateTexture(channels, *widthPtr, *heightPtr, data, repeat, filter);

	//Free data
	stbi_image_free(data);
}

Texture::Texture(unsigned char *data, int width, int height, int channels, bool repeat, bool filter)
{
	tex = Gfx::CreateTexture(channels, width, height, data, repeat, filter);
}

unsigned int Texture::GetID()
{
	return tex;
}

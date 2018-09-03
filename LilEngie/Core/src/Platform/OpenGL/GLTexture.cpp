#include <GL/glew.h>
#include "GLTexture.h"

unsigned int GLTexture::Create(int channels, int width, int height, unsigned char *data, bool repeat, bool filter)
{
	unsigned int tex;

	//Get the format
	GLenum format;
	if (channels == 1)
		format = GL_RED;
	else if (channels == 3)
		format = GL_RGB;
	else if (channels == 4)
		format = GL_RGBA;

	//Setup with opengl
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	//Wrapping
	int wrap = GL_CLAMP;
	if (repeat) wrap = GL_REPEAT;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);

	//Filter
	int fil = GL_LINEAR;
	if (filter) fil = GL_NEAREST;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, fil);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, fil);

	return tex;
}

void GLTexture::CreateDefaultTex(unsigned int *texture)
{
	glGenTextures(1, texture);
	glBindTexture(GL_TEXTURE_2D, *texture);
	char tex[] = { 255, 255, 255, 255 };
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void GLTexture::BindTexture(unsigned int tex, unsigned int slot)
{
	slot = GL_TEXTURE0 + slot;
	glActiveTexture(slot);
	glBindTexture(GL_TEXTURE_2D, tex);
}

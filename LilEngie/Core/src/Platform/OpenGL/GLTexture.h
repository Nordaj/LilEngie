#pragma once

namespace GLTexture
{
	unsigned int Create(int channels, int width, int height, unsigned char *data, bool repeat, bool filter);
	void CreateDefaultTex(unsigned int *texture);
	void BindTexture(unsigned int tex, unsigned int slot);
}

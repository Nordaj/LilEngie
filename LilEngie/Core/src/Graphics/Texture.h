#pragma once

class Texture
{
private:
	unsigned int tex;

public:
	Texture() {}
	Texture(const char *path, bool repeat = true, bool filter = true);
	Texture(unsigned char *data, int width, int height, int channels = 1, bool repeat = false, bool filter = true);

	unsigned int GetID();
};

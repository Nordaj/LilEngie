#pragma once

class Texture
{
private:
	unsigned int tex;

public:
	Texture(const char *path, bool repeat = true, bool filter = true);

	unsigned int GetID();
};
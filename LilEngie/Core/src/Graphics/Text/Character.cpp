#include <Graphics/Texture.h>
#include "Character.h"

Character::Character(Texture tex, int sizeX, int sizeY, int bearingX, int bearingY, float advance)
	:tex(tex), sizeX(sizeX), sizeY(sizeY), bearingX(bearingX), bearingY(bearingY), advance(advance)
{ }

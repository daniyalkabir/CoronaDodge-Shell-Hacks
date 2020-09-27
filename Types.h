#pragma once
#include <stdint.h>

using TextureID = uint32_t;

enum TexID : TextureID
{
	BG,
	PlayerWest,
	PlayerEast,
	PlayerNorth,
	PlayerSouth,
	Enemy,
	PickupMask,
	PickupAmmo,
};

enum EntType
{
	ET_Player,
	ET_Enemy,
	ET_Pickup,
	ET_Streak
};
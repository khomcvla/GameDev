#include "Character.h"

//-------------------------------------------------------------------------------------------------
Character::Character(int x, int y) : Object(x, y)
{
	health = 100;
	characterDirection = ECharacterDirection::right;
}
//-------------------------------------------------------------------------------------------------
Character::~Character()
{
	for (auto& t : textures)
	{
		if (t.second)
		{
			SDL_DestroyTexture(t.second);
		}
	}
}
//-------------------------------------------------------------------------------------------------
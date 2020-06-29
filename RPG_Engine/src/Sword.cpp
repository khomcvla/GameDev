#include "Sword.h"
#include "Texture.h"
#include "Vars.h"

//-------------------------------------------------------------------------------------------------
Sword::Sword(int x, int y) : Weapon(x, y)
{
	texture = Texture::loadTexture("examples/weapons/sword.png");
	description->texture = description->textures["sword"];
}
//-------------------------------------------------------------------------------------------------
int Sword::getDamage() const
{
	return SWORD_DAMAGE;
}
//-------------------------------------------------------------------------------------------------
int Sword::getLength() const
{
	return SWORD_LENGTH;
}
//-------------------------------------------------------------------------------------------------
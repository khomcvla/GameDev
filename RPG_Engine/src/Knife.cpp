#include "Knife.h"
#include "Texture.h"
#include "Vars.h"

//-------------------------------------------------------------------------------------------------
Knife::Knife(int x, int y) : Weapon(x, y)
{
	texture = Texture::loadTexture("examples/weapons/knife.png");
	description->texture = description->textures["knife"];
}
//-------------------------------------------------------------------------------------------------
int Knife::getDamage() const
{
	return KNIFE_DAMAGE;
}
//-------------------------------------------------------------------------------------------------
int Knife::getLength() const
{
	return KNIFE_LENGTH;
}
//-------------------------------------------------------------------------------------------------
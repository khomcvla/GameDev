#include "Weapon.h"
#include "Vars.h"
#include "Texture.h"

//-------------------------------------------------------------------------------------------------
Weapon::Weapon() : Object()
{
	description = std::make_shared<Description>();
	description->texture = description->textures["arm"];
}
//-------------------------------------------------------------------------------------------------
Weapon::Weapon(int x, int y) : Object(x, y)
{
	description = std::make_shared<Description>();
	description->texture = description->textures["arm"];
}
//-------------------------------------------------------------------------------------------------
int Weapon::getDamage() const
{
	return ARM_DAMAGE;
}
//-------------------------------------------------------------------------------------------------
int Weapon::getLength() const
{
	return ARM_LENGTH;
}
//-------------------------------------------------------------------------------------------------

#include "Player.h"
#include "Texture.h"
#include "Inventory.h"

//-------------------------------------------------------------------------------------------------
Player::Player(int x, int y) : Character(x, y)
{
	textures[ECharacterDirection::left] = Texture::loadTexture("examples/characters/player/left.png");
	textures[ECharacterDirection::right] = Texture::loadTexture("examples/characters/player/right.png");
	textures[ECharacterDirection::up] = Texture::loadTexture("examples/characters/player/up.png");
	textures[ECharacterDirection::down] = Texture::loadTexture("examples/characters/player/down.png");

	inventory = std::make_shared<Inventory>();
}
//-------------------------------------------------------------------------------------------------
void Player::update()
{
	texture = textures[characterDirection];
	Character::update();
}
//-------------------------------------------------------------------------------------------------
int Player::getDamage() const
{
	return inventory->weapon->getDamage();
}
//-------------------------------------------------------------------------------------------------
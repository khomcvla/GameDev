#include "Enemy.h"
#include "Texture.h"
#include "Vars.h"

//-------------------------------------------------------------------------------------------------
Enemy::Enemy(int x, int y) : Character(x, y)
{
	if (rand() % 2)
	{
		textures[ECharacterDirection::left] = Texture::loadTexture("examples/characters/enemies/1/left.png");
		textures[ECharacterDirection::right] = Texture::loadTexture("examples/characters/enemies/1/right.png");
	}
	else
	{
		textures[ECharacterDirection::left] = Texture::loadTexture("examples/characters/enemies/2/left.png");
		textures[ECharacterDirection::right] = Texture::loadTexture("examples/characters/enemies/2/right.png");
	}
	step = rand() % 10;
}
//-------------------------------------------------------------------------------------------------
void Enemy::update()
{
	texture = textures[characterDirection];

	if (health <= 0)
	{
		active = false;
	}

	if (characterDirection == ECharacterDirection::right)
	{
		if (step == 10 || step == 20 || step == 30)
		{
			xpos += 64;
			step++;
		}
		else if (step == 40)
		{
			characterDirection = ECharacterDirection::left;
			step = 0;
		}
		else
		{
			step++;
		}
	}
	else if (characterDirection == ECharacterDirection::left)
	{
		if (step == 10 || step == 20 || step == 30)
		{
			xpos -= 64;
			step++;
		}
		else if (step == 40)
		{
			characterDirection = ECharacterDirection::right;
			step = 0;
		}
		else
		{
			step++;
		}
	}

	Character::update();
}
//-------------------------------------------------------------------------------------------------
int Enemy::getDamage() const
{
	return ENEMY_DAMAGE;
}
//-------------------------------------------------------------------------------------------------
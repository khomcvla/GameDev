#include "Health.h"
#include "Texture.h"
#include "Vars.h"

//-------------------------------------------------------------------------------------------------
Health::Health(int x, int y) : Bonus(x, y)
{
	texture = Texture::loadTexture("examples/bonus/health.png");
}
//-------------------------------------------------------------------------------------------------
void Health::addBonusTo(std::shared_ptr<Player>& player)
{
	player->health += HEALTH_BONUS;
	if (player->health > 100)
	{
		player->health = 100;
	}
}
//-------------------------------------------------------------------------------------------------
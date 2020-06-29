#include "Gem.h"
#include "Texture.h"
#include "Vars.h"

//-------------------------------------------------------------------------------------------------
Gem::Gem(int x, int y) : Bonus(x, y)
{
	id = Bonus::current_id;
	if (id % 3 == 0)
	{
		texture = Texture::loadTexture("examples/gems/red.png");
	}
	else if (id % 3 == 1)
	{
		texture = Texture::loadTexture("examples/gems/blue.png");
	}
	else if (id % 3 == 2)
	{
		texture = Texture::loadTexture("examples/gems/green.png");
	}
	Bonus::current_id++;
}
//-------------------------------------------------------------------------------------------------
void Gem::addBonusTo(std::shared_ptr<Player>& player)
{
	player->inventory->gems += 1;
}
//-------------------------------------------------------------------------------------------------
#include "HealthBar.h"
#include "Texture.h"
#include "Vars.h"

//-------------------------------------------------------------------------------------------------
HealthBar::HealthBar(int x, int y) : Object(x, y)
{
	texture = Texture::loadTexture("examples/ui/health_bar.png");
}
//-------------------------------------------------------------------------------------------------
void HealthBar::update()
{
	srcRect.h = HEALTHBAR_HEIGHT;
	srcRect.w = player->health;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = 73;
	destRect.y = SCREEN_HEIGHT - 38;
	destRect.h = srcRect.h;
	destRect.w = srcRect.w;
}
//-------------------------------------------------------------------------------------------------
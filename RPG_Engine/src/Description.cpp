#include "Description.h"
#include "Texture.h"
#include "Vars.h"

//-------------------------------------------------------------------------------------------------
Description::Description() : Object(290, SCREEN_HEIGHT - 38)
{
	textures["arm"] = Texture::loadTexture("examples/weapons/descriptions/arm.png");
	textures["sword"] = Texture::loadTexture("examples/weapons/descriptions/sword.png");
	textures["knife"] = Texture::loadTexture("examples/weapons/descriptions/knife.png");

	texture = textures["arm"];
}
//-------------------------------------------------------------------------------------------------
Description::~Description()
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
void Description::update()
{
	srcRect.h = DESCRIPTION_HEIGHT;
	srcRect.w = DESCRIPTION_WIDTH;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = 290;
	destRect.y = SCREEN_HEIGHT - 49;
	destRect.h = srcRect.h;
	destRect.w = srcRect.w;
}
//-------------------------------------------------------------------------------------------------
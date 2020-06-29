#include "Object.h"
#include "Game.h"
#include "Texture.h"
#include "Vars.h"

#include <string>

//-------------------------------------------------------------------------------------------------
Object::Object()
{
}
//-------------------------------------------------------------------------------------------------
Object::Object(int x, int y)
{
	xpos = x;
	ypos = y;

	srcRect.h = TEXTURE_SIZE;
	srcRect.w = TEXTURE_SIZE;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.h = srcRect.h;
	destRect.w = srcRect.w;
}
//-------------------------------------------------------------------------------------------------
Object::~Object()
{
	if (texture)
	{
		SDL_DestroyTexture(texture);
	}
}
//-------------------------------------------------------------------------------------------------
void Object::update()
{
	srcRect.h = TEXTURE_SIZE;
	srcRect.w = TEXTURE_SIZE;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.h = srcRect.h;
	destRect.w = srcRect.w;
}
//-------------------------------------------------------------------------------------------------
void Object::render()
{
	if (texture)
	{
		SDL_RenderCopyEx(Game::renderer, texture, &srcRect, &destRect, 0.0, NULL, SDL_FLIP_NONE);
	}
}
//-------------------------------------------------------------------------------------------------
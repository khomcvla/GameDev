#include "Texture.h"
#include "Game.h"

//#include <SDL2/SDL_image.h>
#include <SDL_image.h>

//-------------------------------------------------------------------------------------------------
SDL_Texture* Texture::loadTexture(const std::string& file)
{
	SDL_Surface* tempSurface = IMG_Load(file.c_str());
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	return texture;
}
//-------------------------------------------------------------------------------------------------
void Texture::draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest)
{
	SDL_RenderCopy(Game::renderer, texture, &src, &dest);
}
//-------------------------------------------------------------------------------------------------

#include "EndGame.h"
#include "Texture.h"
#include "Vars.h"

//-------------------------------------------------------------------------------------------------
EndGame::EndGame(int x, int y) : Object(x, y)
{
	textures["the_end"] = Texture::loadTexture("examples/screen/the_end.png");
	textures["game_over"] = Texture::loadTexture("examples/screen/game_over.png");

	texture = textures["the_end"];
}
//-------------------------------------------------------------------------------------------------
EndGame::~EndGame()
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
void EndGame::update()
{
	srcRect.h = SCREEN_HEIGHT;
	srcRect.w = SCREEN_WIDTH;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.h = srcRect.h;
	destRect.w = srcRect.w;
}
//-------------------------------------------------------------------------------------------------
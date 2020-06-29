#include "Game.h"
#include "Vars.h"

#include <memory>
#include <SDL.h>
//#include <SDL2/SDL.h>

//-------------------------------------------------------------------------------------------------
int main(int argc, char* argv[])
{
	const int FPS = 30;
	const int frameDelayMenu = 2000 / FPS;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	std::shared_ptr<Game> game = std::make_shared<Game>("RPG Game Engine 1.0", SCREEN_WIDTH, SCREEN_HEIGHT, false);

	while (game->isMenu())
	{
		frameStart = SDL_GetTicks();

		game->handleEventsMenu();
		game->updateMenu();
		game->renderMenu();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelayMenu > frameTime)
		{
			SDL_Delay(frameDelayMenu - frameTime);
		}
	}

	game->init();

	while (game->isRunning())
	{
		frameStart = SDL_GetTicks();

		game->handleEventsRunning();
		game->updateRunning();
		game->renderRunning();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	while (game->isEndGame())
	{
		frameStart = SDL_GetTicks();

		game->handleEventsEndGame();
		game->updateEndGame();
		game->renderEndGame();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();
	return 0;
}
//-------------------------------------------------------------------------------------------------

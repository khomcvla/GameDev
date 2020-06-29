#ifndef GAME_H
#define GAME_H

#include <string>
#include <SDL.h>
//#include <SDL2/SDL.h>

//-------------------------------------------------------------------------------------------------
/**
 * @brief The class represents the game and handles game events
 */
class Game
{
public:
	//-------------------------------------------------------------------------
	/**
	 *	@brief Constructor that initializes the game
	 *
	 * 	@param[in] title Game title
	 * 	@param[in] width Screen width
	 * 	@param[in] height Screen height
	 * 	@param[in] fullscreen Fullscreen mode
	 */
	Game(const std::string& title, int width, int height, bool fullscreen);

	//-------------------------------------------------------------------------
	/**
	 *	@brief Initiate a new game
	 */
	void init();

	//-------------------------------------------------------------------------
	/**
	 *	@brief Save game
	 */
	void saveGame();

	//-------------------------------------------------------------------------
	/**
	 *	@brief Load saved game
	 */
	void loadGame();

	//-------------------------------------------------------------------------
	/**
	 *	@brief Cleans game resources before quit
	 */
	void clean();

	//-------------------------------------------------------------------------
	/**
	 *	@brief Checks if the menu screen is displayed at this moment
	 */
	bool isMenu();

	//-------------------------------------------------------------------------
	/**
	 *	@brief Handles events on the menu screen
	 */
	void handleEventsMenu();

	//-------------------------------------------------------------------------
	/**
	 *	@brief Updates all objects on the menu screen
	 */
	void updateMenu();

	//-------------------------------------------------------------------------
	/**
	 *	@brief Renders all objects on the menu screen
	 */
	void renderMenu();

	//-------------------------------------------------------------------------
	/**
	 *	@brief Checks if the game is running at this moment
	 */
	bool isRunning();

	//-------------------------------------------------------------------------
	/**
	 *	@brief Handles events during the game
	 */
	void handleEventsRunning();

	//-------------------------------------------------------------------------
	/**
	 *	@brief Updates all objects during the game
	 */
	void updateRunning();

	//-------------------------------------------------------------------------
	/**
	 *	@brief Renders all objects during the game
	 */
	void renderRunning();

	//-------------------------------------------------------------------------
	/**
	 *	@brief Checks if the endgame screen is displayed at this moment
	 */
	bool isEndGame();

	//-------------------------------------------------------------------------
	/**
	 *	@brief Handles events on the endgame screen
	 */
	void handleEventsEndGame();

	//-------------------------------------------------------------------------
	/**
	 *	@brief Updates all objects on the endgame screen
	 */
	void updateEndGame();

	//-------------------------------------------------------------------------
	/**
	 *	@brief Render all objects on the endgame screen
	 */
	void renderEndGame();

public:
	static SDL_Renderer* renderer; ///< Renderer

private:
	bool isLoadedFromSave;

	bool onMenu;
	bool onRunning;
	bool onEndGame;

	SDL_Window* window;
	SDL_Event event;
	const Uint8* keystate;
};
//-------------------------------------------------------------------------------------------------
#endif // GAME_H

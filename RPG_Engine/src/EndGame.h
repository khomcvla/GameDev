#ifndef ENDGAME_H
#define ENDGAME_H

#include "Object.h"

#include <map>
#include <string>
#include <SDL.h>
//#include <SDL2/SDL.h>

//-------------------------------------------------------------------------------------------------
/**
 *	@brief The class represents the last screen at the end of the game
 */
class EndGame : public Object
{
public:
	~EndGame();

	//-------------------------------------------------------------------------
	/**
	 *	@brief Constructor that initializes a new EndGame at (x,y) coordinates
	 *
	 * 	@param[in] x Position x-coordinate
	 * 	@param[in] y Position y-coordinate
	 */
	EndGame(int x, int y);

	//-------------------------------------------------------------------------
	/**
	 * @brief Virtual method to update EndGame
	 */
	void update() override;

public:
	std::map<std::string, SDL_Texture*> textures; ///< Textures for the last screen at the end of the game
};
//-------------------------------------------------------------------------------------------------
#endif // ENDGAME_H

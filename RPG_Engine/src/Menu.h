#ifndef MENU_H
#define MENU_H

#include "Object.h"

#include <SDL.h>
//#include <SDL2/SDL.h>

//-------------------------------------------------------------------------------------------------
/**
 *	@brief The class represents the menu at the beginning of the game
 */
class Menu : public Object
{
public:
	//-------------------------------------------------------------------------
	/**
	 *	@brief Constructor that initializes a new Menu at (x,y) coordinates
	 *
	 * 	@param[in] x Position x-coordinate
	 * 	@param[in] y Position y-coordinate
	 */
	Menu(int x, int y);

	//-------------------------------------------------------------------------
	/**
	 * @brief Virtual method to update Menu
	 */
	void update() override;
};
//-------------------------------------------------------------------------------------------------
#endif // MENU_H

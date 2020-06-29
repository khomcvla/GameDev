#ifndef OBJECT_H
#define OBJECT_H

#include <SDL.h>
//#include <SDL2/SDL.h>

//-------------------------------------------------------------------------------------------------
/**
 * @brief The class represents the parent class for all game objects
 */
class Object
{
public:
	~Object();
	Object();

	//-------------------------------------------------------------------------
	/**
	 *	@brief Constructor that initializes a new Object at (x,y) coordinates
	 *
	 * 	@param[in] x Position x-coordinate
	 * 	@param[in] y Position y-coordinate
	 */
	Object(int x, int y);

	//-------------------------------------------------------------------------
	/**
	 * @brief Virtual method to update Object
	 */
	virtual void update();

	//-------------------------------------------------------------------------
	/**
	 * @brief Virtual method to render Object
	 */
	virtual void render();

public:
	bool active = true; ///< Object state

	int xpos; ///< Position x-coordinate
	int ypos; ///< Position y-coordinate

	SDL_Rect srcRect; ///< Variable to render object texture on the screen
	SDL_Rect destRect; ///< Variable to render object texture on the screen

	SDL_Texture* texture = nullptr; ///< Object texture
};
//-------------------------------------------------------------------------------------------------
#endif // OBJECT_H

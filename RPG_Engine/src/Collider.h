#ifndef COLLIDER_H
#define COLLIDER_H

#include "Object.h"

//-------------------------------------------------------------------------------------------------
/**
 *	@brief The class represents a collider on the map which restrict characters movement
 */
class Collider : public Object
{
public:
	//-------------------------------------------------------------------------
	/**
	 *	@brief Constructor that initializes a new collider at (x,y) coordinates
	 *
	 * 	@param[in] x 		Position x-coordinate
	 * 	@param[in] y 		Position y-coordinate
	 *  @param[in] isGrid   Сollider texture visibility. This parameter is false by default
	 */
	Collider(int x, int y, bool isGrid = false);

public:
	static int current_id;
	int id = 0; ///< Collider id
};
//-------------------------------------------------------------------------------------------------
#endif // COLLIDER_H
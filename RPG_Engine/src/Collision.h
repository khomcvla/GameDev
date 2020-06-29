#ifndef COLLISION_H
#define COLLISION_H

#include "Object.h"

#include <memory>
#include <SDL.h>
//#include <SDL2/SDL.h>

//-------------------------------------------------------------------------------------------------
/**
 *	@brief The class represents collision detection
 */
class Collision
{
public:
	//-------------------------------------------------------------------------
	/**
	 *  @brief A static method for collision detection between two objects
	 *
	 * 	@param[in] objA The first object
	 * 	@param[in] objB The second object
	 *
	 *	@return true || false
	 */
	static bool AABB(const std::shared_ptr<Object>& objA, const std::shared_ptr<Object>& ojbB);
};
//-------------------------------------------------------------------------------------------------
#endif // COLLISION_H

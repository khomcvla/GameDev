#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"

//-------------------------------------------------------------------------------------------------
/**
 *	@brief The class represents the child of the parent class Character
 */
class Enemy : public Character
{
public:
	//-------------------------------------------------------------------------
	/**
	 *	@brief Constructor that initializes a new Knife at (x,y) coordinates
	 *
	 * 	@param[in] x Position x-coordinate
	 * 	@param[in] y Position y-coordinate
	 */
	Enemy(int x, int y);

	//-------------------------------------------------------------------------
	/**
	 * @brief Virtual method to update Enemy
	 */
	void update() override;

	//-------------------------------------------------------------------------
	/**
	 *	@brief A virtual method that returns Enemy damage
	 *
	 * 	@return Enemy damage
	 */
	int getDamage() const;

public:
	int step; ///< Variable for moving enemies on the map
};
//-------------------------------------------------------------------------------------------------
#endif // ENEMY_H
#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include "Inventory.h"

#include <memory>

//-------------------------------------------------------------------------------------------------
/**
 *	@brief The class represents the child of the parent class Character
 */
class Player : public Character
{
public:
	//-------------------------------------------------------------------------
	/**
	 *	@brief Constructor that initializes a new Player at (x,y) coordinates
	 *
	 * 	@param[in] x Position x-coordinate
	 * 	@param[in] y Position y-coordinate
	 */
	Player(int x, int y);

	//-------------------------------------------------------------------------
	/**
	 *	@brief Virtual method to update Player
	 */
	void update() override;

	//-------------------------------------------------------------------------
	/**
	 *	@brief A virtual method that returns Player damage
	 *
	 *	@details Damage is based on the weapon that the player currently has
	 *
	 * 	@return Player's weapon damage
	 */
	int getDamage() const;

public:
	std::shared_ptr<Inventory> inventory; ///< Player's inventory
};
//-------------------------------------------------------------------------------------------------
#endif // PLAYER_H
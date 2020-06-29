#ifndef BONUS_H
#define BONUS_H

#include "Object.h"
#include "Player.h"

#include <memory>

//-------------------------------------------------------------------------------------------------
/**
 *	@brief  The class represents the parent class for all bonuses
 */
class Bonus : public Object
{
public:
	//-------------------------------------------------------------------------
	/**
	 *	@brief Constructor that initializes a new Bonus at (x,y) coordinates
	 *
	 * 	@param[in] x Position x-coordinate
	 * 	@param[in] y Position y-coordinate
	 */
	Bonus(int x, int y);

	//-------------------------------------------------------------------------
	/**
	 *	@brief A virtual method that adds a bonus to the player who found it
	 *
	 *	@param[in] player The player who found it
	 */
	virtual void addBonusTo(std::shared_ptr<Player>& player) = 0;

public:
	static int current_id;
	int id = 0; ///< Bonus id
};
//-------------------------------------------------------------------------------------------------
#endif // BONUS_H
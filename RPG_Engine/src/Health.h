#ifndef HEALTH_H
#define HEALTH_H

#include "Bonus.h"
#include "Player.h"

//-------------------------------------------------------------------------------------------------
/**
 *	@brief The class represents the child of the parent class Bonus
 */
class Health : public Bonus
{
public:
	//-------------------------------------------------------------------------
	/**
	 *	@brief Constructor that initializes a new Health at (x,y) coordinates
	 *
	 * 	@param[in] x Position x-coordinate
	 * 	@param[in] y Position y-coordinate
	 */
	Health(int x, int y);

	//-------------------------------------------------------------------------
	/**
	 *	@brief A virtual method that adds health to the player who found it
	 *
	 *	@param[in] player The player who found it
	 */
	void addBonusTo(std::shared_ptr<Player>& player) override;
};
//-------------------------------------------------------------------------------------------------
#endif // HEALTH_H
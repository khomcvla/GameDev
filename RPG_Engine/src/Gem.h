#ifndef GEM_H
#define GEM_H

#include "Bonus.h"
#include "Player.h"

//-------------------------------------------------------------------------------------------------
/**
 *	@brief The class represents the child of the parent class Bonus
 */
class Gem : public Bonus
{
public:
	//-------------------------------------------------------------------------
	/**
	 *	@brief Constructor that initializes a new Gem at (x,y) coordinates
	 *
	 * 	@param[in] x Position x-coordinate
	 * 	@param[in] y Position y-coordinate
	 */
	Gem(int x, int y);

	//-------------------------------------------------------------------------
	/**
	 *	@brief A virtual method that adds a gem to the player who found it
	 *
	 *	@param[in] player The player who found it
	 */
	void addBonusTo(std::shared_ptr<Player>& player) override;
};
//-------------------------------------------------------------------------------------------------
#endif // GEM_H
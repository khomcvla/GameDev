#ifndef KNIFE_H
#define KNIFE_H

#include "Weapon.h"

//-------------------------------------------------------------------------------------------------
/**
 *	@brief The class represents the child of the parent class Weapon
 */
class Knife : public Weapon
{
public:
	//-------------------------------------------------------------------------
	/**
	 *	@brief Constructor that initializes a new Knife at (x,y) coordinates
	 *
	 * 	@param[in] x Position x-coordinate
	 * 	@param[in] y Position y-coordinate
	 */
	Knife(int x, int y);

	//-------------------------------------------------------------------------
	/**
	 *	@brief A virtual method that returns Knife damage
	 *
	 * 	@return Knife damage
	 */
	int getDamage() const override;

	//-------------------------------------------------------------------------
	/**
	 * 	@brief A virtual method that returns Knife length
	 *
	 * 	@return Knife length
	 */
	int getLength() const override;
};
//-------------------------------------------------------------------------------------------------
#endif // KNIFE_H
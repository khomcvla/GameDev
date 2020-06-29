#ifndef SWORD_H
#define SWORD_H

#include "Weapon.h"

//-------------------------------------------------------------------------------------------------
/**
 *	@brief The class represents the child of the parent class Weapon
 */
class Sword : public Weapon
{
public:
	//-------------------------------------------------------------------------
	/**
	 *	@brief Constructor that initializes a new Sword at (x,y) coordinates
	 *
	 * 	@param[in] x Position x-coordinate
	 * 	@param[in] y Position y-coordinate
	 */
	Sword(int x, int y);

	//-------------------------------------------------------------------------
	/**
	 *	@brief A virtual method that returns Sword damage
	 *
	 * 	@return Sword damage
	 */
	int getDamage() const override;

	//-------------------------------------------------------------------------
	/**
	 * 	@brief A virtual method that returns Sword length
	 *
	 * 	@return Sword length
	 */
	int getLength() const override;
};
//-------------------------------------------------------------------------------------------------
#endif // SWORD_H
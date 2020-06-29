#ifndef WEAPON_H
#define WEAPON_H

#include "Object.h"
#include "Description.h"

#include <memory>

//-------------------------------------------------------------------------------------------------
/**
 *	@brief The class represents the default weapon that a player starts with and the parent class for all weapons
 */
class Weapon : public Object
{
public:
	Weapon();

	//-------------------------------------------------------------------------
	/**
	 *	@brief Constructor that initializes a new Weapon at (x,y) coordinates
	 *
	 * 	@param[in] x Position x-coordinate
	 * 	@param[in] y Position y-coordinate
	 */
	Weapon(int x, int y);

	//-------------------------------------------------------------------------
	/**
	 *	@brief A virtual method that returns Weapon damage
	 *
	 * 	@return Weapon damage
	 */
	virtual int getDamage() const;

	//-------------------------------------------------------------------------
	/**
	 * 	@brief A virtual method that returns Weapon length
	 *
	 * 	@return Weapon length
	 */
	virtual int getLength() const;

public:
	std::shared_ptr<Description> description; ///< Weapon description displayed in inventory
};
//-------------------------------------------------------------------------------------------------
#endif // WEAPON_H
#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include "Object.h"
#include "Player.h"

#include <memory>

//-------------------------------------------------------------------------------------------------
/**
 *	@brief The class represents a bar for the player's health
 */
class HealthBar : public Object
{
public:
	//-------------------------------------------------------------------------
	/**
	 *	@brief Constructor that initializes a new HealthBar at (x,y) coordinates
	 *
	 * 	@param[in] x Position x-coordinate
	 * 	@param[in] y Position y-coordinate
	 */
	HealthBar(int x, int y);

	//-------------------------------------------------------------------------
	/**
	 *	@brief Virtual method to update HealthBar
	 */
	void update() override;

public:
	std::shared_ptr<Player> player; ///< Linking between Player and his HealthBar 
};
//-------------------------------------------------------------------------------------------------
#endif // HEALTHBAR_H
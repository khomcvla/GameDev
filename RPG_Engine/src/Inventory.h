#ifndef INVENTORY_H
#define INVENTORY_H

#include "Object.h"
#include "Weapon.h"

#include <memory>

//-------------------------------------------------------------------------------------------------
/**
 *	@brief The class represents player's inventory
 */
class Inventory : public Object
{
public:
	Inventory();

	//-------------------------------------------------------------------------
	/**
	 * @brief Virtual method to update Inventory
	 */
	void update() override;

public:
	int gems; ///< Variable for counting gems
	std::shared_ptr<Weapon> weapon; ///< Player's weapon
};
//-------------------------------------------------------------------------------------------------
#endif // INVENTORY_H
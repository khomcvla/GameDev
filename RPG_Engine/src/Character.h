#ifndef CHARACTER_H
#define CHARACTER_H

#include "Collider.h"

#include <map>

//-------------------------------------------------------------------------------------------------
/**
 *	@brief The class represents the parent class for all characters
 */
class Character : public Object
{
public:
	/// A set of possible character direction states
	enum class ECharacterDirection
	{
		left, 	///< Character moves to the left
		right, 	///< Character moves to the right
		up,		///< Character moves to the up
		down	///< Character moves to the down
	};

public:
	~Character();

	//-------------------------------------------------------------------------
	/**
	 *	@brief Constructor that initializes a new Character at (x,y) coordinates
	 *
	 * 	@param[in] x Position x-coordinate
	 * 	@param[in] y Position y-coordinate
	 */
	Character(int x, int y);

	//-------------------------------------------------------------------------
	/**
	 *	@brief A virtual method that returns Character damage
	 *
	 * 	@return Character's damage
	 */
	virtual int getDamage() const = 0;

public:
	int health; ///< Character's health
	ECharacterDirection characterDirection; ///< Character direction
	std::map<ECharacterDirection, SDL_Texture*> textures; ///< Textures for directions
};
//-------------------------------------------------------------------------------------------------
#endif // CHARACTER_H
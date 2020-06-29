#ifndef DESCRIPTION_H
#define DESCRIPTION_H

#include "Object.h"

#include <map>
#include <string>

//-------------------------------------------------------------------------------------------------
/**
 *	@brief The class represents description of player's weapon
 */
class Description : public Object
{
public:
	~Description();
	Description();

	//-------------------------------------------------------------------------
	/**
	 * @brief A virtual method that updates weapon description
	 */
	void update() override;

public:
	std::map<std::string, SDL_Texture*> textures; ///< Textures with descriptions for each weapon
};
//-------------------------------------------------------------------------------------------------
#endif // DESCRIPTION_H
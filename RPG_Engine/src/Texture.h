#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

#include <SDL.h>
// #include <SDL2/SDL.h> 

//-------------------------------------------------------------------------------------------------
/**
 *	@brief The class represents loading and drawing texture helper
 */
class Texture
{
public:
	//-------------------------------------------------------------------------
	/**
	 *  @brief A static method that helps to load and prepare a new texture
	 *
	 * 	@param[in] file Texture file path
	 *
	 *	@return Created SDL_Texture*
	 */
	static SDL_Texture* loadTexture(const std::string& file);

	//-------------------------------------------------------------------------
	/**
	 *  @brief A static method that helps to draw selected texture
	 *
	 * 	@param[in] texture Selected texture
	 * 	@param[in] src Source rectangle for the texture
	 * 	@param[out] dest Destination rectangle for the texture
	 */
	static void draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest);
};
//-------------------------------------------------------------------------------------------------
#endif // TEXTURE_H

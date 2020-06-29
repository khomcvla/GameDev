#ifndef MAP_H
#define MAP_H

#include "Vars.h"
#include "Player.h"
#include "Enemy.h"
#include "Bonus.h"

#include <map>
#include <fstream>
#include <memory>
#include <vector>
#include <SDL.h>
//#include <SDL2/SDL.h>

//-------------------------------------------------------------------------------------------------
/**
 *	@brief The class represents levels loader and map drawer
 */
class Map
{
public:
	~Map();

	//-------------------------------------------------------------------------
	/**
	 *	@brief Constructor
	 *
	 * 	@param[in, out] colliders All colliders in the game
	 * 	@param[in, out] enemies All enemies in the game
	 * 	@param[in, out] weapons All weapons in the game
	 * 	@param[in, out] bonuses All bonuses in the game
	 */
	Map(std::map<int, std::vector<std::shared_ptr<Collider>>>* colliders,
		std::map<int, std::vector<std::shared_ptr<Enemy>>>* enemies,
		std::map<int, std::vector<std::shared_ptr<Weapon>>>* weapons,
		std::map<int, std::vector<std::shared_ptr<Bonus>>>* bonuses);

	//-------------------------------------------------------------------------
	/**
	 *	@brief Loads current level on the map
	 *
	 *  @param[in] number Current level number
	 *  @param[in] isSaveLoaded Game is loaded from saves (true) or started from the beginning (false)
	 */
	void load(int number);

	//-------------------------------------------------------------------------
	/**
	 *	@brief Draws the current level on the map
	 */
	void draw();

public:
	SDL_Rect src; ///< Variable to map textures on the screen
	SDL_Rect dest; ///< Variable to map textures on the screen

	std::map<std::string, SDL_Texture*> textures; ///< Prepared map textures
	std::map<int, char[MAP_HEIGHT][MAP_WIDTH]> mapTextures; ///< Loaded levels with map textures from files

	int level; ///< Current level
	std::vector<bool> isLevelLoaded; ///< Level loading status
	std::map<int, std::string> levels; ///< Path to the levels

	std::map<int, std::vector<std::shared_ptr<Collider>>>* colliders; ///< All colliders in the game
	std::map<int, std::vector<std::shared_ptr<Enemy>>>* enemies; ///< All enemies in the game
	std::map<int, std::vector<std::shared_ptr<Weapon>>>* weapons; ///< All weapons in the game
	std::map<int, std::vector<std::shared_ptr<Bonus>>>* bonuses; ///< All bonuses in the game
};
//-------------------------------------------------------------------------------------------------
#endif // MAP_H

#include "Map.h"
#include "Texture.h"
#include "Player.h"
#include "Vars.h"
#include "Game.h"
#include "Enemy.h"
#include "Knife.h"
#include "Sword.h"
#include "Health.h"
#include "Gem.h"

//-------------------------------------------------------------------------------------------------
Map::Map(std::map<int, std::vector<std::shared_ptr<Collider>>>* colliders,
	std::map<int, std::vector<std::shared_ptr<Enemy>>>* enemies,
	std::map<int, std::vector<std::shared_ptr<Weapon>>>* weapons,
	std::map<int, std::vector<std::shared_ptr<Bonus>>>* bonuses)
{
	std::vector<bool> temp(5, false);
	this->isLevelLoaded = temp;
	this->colliders = colliders;
	this->enemies = enemies;
	this->weapons = weapons;
	this->bonuses = bonuses;

	src.x = 0;
	src.y = 0;
	src.w = TEXTURE_SIZE;
	src.h = TEXTURE_SIZE;

	dest.x = 0;
	dest.y = 0;
	dest.w = TEXTURE_SIZE;
	dest.h = TEXTURE_SIZE;

	textures["grass"] = Texture::loadTexture("examples/map/grass.png");
	textures["floor"] = Texture::loadTexture("examples/map/floor.png");
	textures["wall"] = Texture::loadTexture("examples/map/wall.png");
	textures["block"] = Texture::loadTexture("examples/map/block.png");
	textures["dirt"] = Texture::loadTexture("examples/map/dirt.png");
	textures["wood"] = Texture::loadTexture("examples/map/wood.png");
	textures["grid"] = Texture::loadTexture("examples/map/grid.png");
	textures["lib"] = Texture::loadTexture("examples/map/lib.png");

	levels[1] = "examples/levels/1.lvl";
	levels[2] = "examples/levels/2.lvl";
	levels[3] = "examples/levels/3.lvl";
	levels[4] = "examples/levels/4.lvl";
	levels[5] = "examples/levels/5.lvl";
}
//-------------------------------------------------------------------------------------------------
Map::~Map()
{
	for (auto& t : textures)
	{
		if (t.second)
		{
			SDL_DestroyTexture(t.second);
		}
	}
}
//-------------------------------------------------------------------------------------------------
void Map::load(int level)
{
	this->level = level;

	if (!isLevelLoaded[level - 1])
	{
		char c;
		std::ifstream file;
		file.open(levels[level].c_str());

		isLevelLoaded[level - 1] = true;

		// textures
		for (int row = 0; row < MAP_HEIGHT; row++)
		{
			for (int col = 0; col < MAP_WIDTH; col++)
			{
				file.get(c);
				mapTextures[level][row][col] = c;
			}
			file.ignore();
		}

		file.ignore();

		// colliders | enemies | weapons | bonuses 
		for (int row = 0; row < MAP_HEIGHT; row++)
		{
			for (int col = 0; col < MAP_WIDTH; col++)
			{
				file.get(c);
				if (c == '1')
				{
					(*colliders)[level].push_back(std::make_shared<Collider>(col * TEXTURE_SIZE, row * TEXTURE_SIZE));
				}
				else if (c == '+')
				{
					(*colliders)[level].push_back(std::make_shared<Collider>(col * TEXTURE_SIZE, row * TEXTURE_SIZE, true));
				}
				else if (c == 'E')
				{
					(*enemies)[level].push_back(std::make_shared<Enemy>(col * TEXTURE_SIZE, row * TEXTURE_SIZE));
				}
				else if (c == 'K')
				{
					(*weapons)[level].push_back(std::make_shared<Knife>(col * TEXTURE_SIZE, row * TEXTURE_SIZE));
				}
				else if (c == 'S')
				{
					(*weapons)[level].push_back(std::make_shared<Sword>(col * TEXTURE_SIZE, row * TEXTURE_SIZE));
				}
				else if (c == 'H')
				{
					(*bonuses)[level].push_back(std::make_shared<Health>(col * TEXTURE_SIZE, row * TEXTURE_SIZE));
				}
				else if (c == 'G')
				{
					(*bonuses)[level].push_back(std::make_shared<Gem>(col * TEXTURE_SIZE, row * TEXTURE_SIZE));
				}
			}
			file.ignore();
		}
		file.close();
	}
}
//-------------------------------------------------------------------------------------------------
void Map::draw()
{
	char type;
	for (int row = 0; row < MAP_HEIGHT; row++)
	{
		for (int col = 0; col < MAP_WIDTH; col++)
		{
			dest.x = col * TEXTURE_SIZE;
			dest.y = row * TEXTURE_SIZE;

			type = mapTextures[level][row][col];
			switch (type)
			{
			case '!':
				Texture::draw(textures["grass"], src, dest);
				break;

			case '.':
				Texture::draw(textures["floor"], src, dest);
				break;

			case '#':
				Texture::draw(textures["wall"], src, dest);
				break;

			case '=':
				Texture::draw(textures["block"], src, dest);
				break;

			case '_':
				Texture::draw(textures["lib"], src, dest);
				break;

			case '~':
				Texture::draw(textures["dirt"], src, dest);
				break;

			case '-':
				Texture::draw(textures["wood"], src, dest);
				break;

			default:
				break;
			}
		}
	}
}
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "Texture.h"
#include "Object.h"
#include "Menu.h"
#include "Player.h"
#include "Enemy.h"
#include "Map.h"
#include "Vars.h"
#include "Collision.h"
#include "Inventory.h"
#include "Health.h"
#include "Knife.h"
#include "Sword.h"
#include "EndGame.h"
#include "HealthBar.h"

#include <string>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include <SDL.h>
#include "Gem.h"
//#include <SDL2/SDL.h>

//-------------------------------------------------------------------------------------------------
std::shared_ptr<Menu> menu;
std::shared_ptr<Object> selector;
int selectorPosition;

std::shared_ptr<Player> player;
std::shared_ptr<Map> map;
std::shared_ptr<HealthBar> healthBar;
std::shared_ptr<EndGame> endGame;

std::shared_ptr<Object> attack;
std::map<Character::ECharacterDirection, SDL_Texture*> attackKnife;
std::map<Character::ECharacterDirection, SDL_Texture*> attackSword;

std::map<int, std::vector<std::shared_ptr<Collider>>> colliders;
std::map<int, std::vector<std::shared_ptr<Enemy>>> enemies;
std::map<int, std::vector<std::shared_ptr<Weapon>>> weapons;
std::map<int, std::vector<std::shared_ptr<Bonus>>> bonuses;

SDL_Renderer* Game::renderer = nullptr;
//-------------------------------------------------------------------------------------------------
Game::Game(const std::string& title, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		isLoadedFromSave = false;

		onMenu = true;
		onRunning = true;
		onEndGame = true;
	}
	else
	{
		isLoadedFromSave = false;

		onMenu = false;
		onRunning = false;
		onEndGame = false;
	}

	// Menu
	menu = std::make_shared<Menu>(0, 0);
	selector = std::make_shared<Object>(0, 0);
	selector->texture = Texture::loadTexture("examples/screen/selector.png");
	selectorPosition = 0;

	// EndGame
	endGame = std::make_shared<EndGame>(0, 0);

	// prepare Knife texture for fight
	attackKnife[Character::ECharacterDirection::left] = Texture::loadTexture("examples/weapons/attack/knife/left.png");
	attackKnife[Character::ECharacterDirection::right] = Texture::loadTexture("examples/weapons/attack/knife/right.png");
	attackKnife[Character::ECharacterDirection::up] = Texture::loadTexture("examples/weapons/attack/knife/up.png");
	attackKnife[Character::ECharacterDirection::down] = Texture::loadTexture("examples/weapons/attack/knife/down.png");

	// prepare Sword texture for fight
	attackSword[Character::ECharacterDirection::left] = Texture::loadTexture("examples/weapons/attack/sword/left.png");
	attackSword[Character::ECharacterDirection::right] = Texture::loadTexture("examples/weapons/attack/sword/right.png");
	attackSword[Character::ECharacterDirection::up] = Texture::loadTexture("examples/weapons/attack/sword/up.png");
	attackSword[Character::ECharacterDirection::down] = Texture::loadTexture("examples/weapons/attack/sword/down.png");
}
//-------------------------------------------------------------------------------------------------
void Game::init()
{
	// prepare player
	player = std::make_shared<Player>(64, 64 * 5);
	player->characterDirection = Character::ECharacterDirection::down;

	// prepare texture for fight
	attack = std::make_shared<Object>(0, 0);
	attack->active = false;

	// prepare player health bar
	healthBar = std::make_shared<HealthBar>(71, SCREEN_WIDTH - 22);
	healthBar->player = player;

	// load the 1st level
	map = std::make_shared<Map>(&colliders, &enemies, &weapons, &bonuses);

	if (isLoadedFromSave)
	{
		loadGame();
	}
	else
	{
		map->load(1);
	}
}
//-------------------------------------------------------------------------------------------------
void Game::loadGame()
{
	int cnt;
	char cnt_buffer[6];

	char player_buffer[18];
	char collider_buffer[16];
	char enemies_buffer[21];
	char weapons_buffer[14];
	char bonuses_buffer[14];

	char c;
	std::ifstream file;
	file.open("examples/saves/1.save");

	//----------------------------------------------
	// Map

	// get the current level
	file.get(c);
	map->level = atoi(&c);
	file.ignore();

	// read how many levels are saved
	for (int level = 0; level < 5; level++)
	{
		file.get(c);
		map->isLevelLoaded[level] = atoi(&c);
	}
	file.ignore();

	// read level by level
	for (int level = 0; level < 5; level++)
	{
		if (map->isLevelLoaded[level])
		{
			for (int row = 0; row < MAP_HEIGHT; row++)
			{
				for (int col = 0; col < MAP_WIDTH; col++)
				{
					file.get(c);
					map->mapTextures[level + 1][row][col] = c;
				}
				file.ignore();
			}
			file.ignore();
		}
	}

	//----------------------------------------------
	// Player

	// get '['
	file.get(c);

	// get a Player object and then construct it from a part of buffer using initializer list
	file.get(player_buffer, 18);

	// (xxx;xxx;xxx;x) <==> (xpos; ypos; health; direction)
	int xpos = std::stoi(std::string({ player_buffer[1], player_buffer[2], player_buffer[3] }));
	int ypos = std::stoi(std::string({ player_buffer[5], player_buffer[6], player_buffer[7] }));
	int health = std::stoi(std::string({ player_buffer[9], player_buffer[10], player_buffer[11] }));
	int gems = std::stoi(std::string({ player_buffer[13] }));
	int direction = std::stoi(std::string({ player_buffer[15] }));

	player->xpos = xpos;
	player->ypos = ypos;
	player->health = health;	
	player->inventory->gems = gems;
	player->characterDirection = static_cast<Character::ECharacterDirection>(direction);

	if (gems >= 2)
	{
		Collider::current_id = 10;
	}

	// get ']'
	file.get(c);
	file.ignore();
	file.ignore();

	//----------------------------------------------
	// Colliders

	// get '['
	file.get(c);

	// get the number of colliders
	file.get(cnt_buffer, 6);
	cnt = std::stoi(std::string({ cnt_buffer[1], cnt_buffer[2], cnt_buffer[3] }));

	// read colliders
	for (int i = 0; i < cnt; i++)
	{
		// get a Collider object and then construct it from a part of buffer using initializer list
		file.get(collider_buffer, 16);

		// (x;x;xxx;xxx) <==> (level; id; xpos; ypos)
		// ( 1 ; 3 4 5 ; 7 8 9 ; 11 12 13 )
		int level = std::stoi(std::string({ collider_buffer[1] }));

		int id = std::stoi(std::string({ collider_buffer[3], collider_buffer[4], collider_buffer[5] }));
		int xpos = std::stoi(std::string({ collider_buffer[7], collider_buffer[8], collider_buffer[9] }));
		int ypos = std::stoi(std::string({ collider_buffer[11], collider_buffer[12], collider_buffer[13] }));

		std::shared_ptr<Collider> collider = std::make_shared<Collider>(xpos, ypos, id);
		collider->id = id;

		if (id > Collider::current_id)
		{
			Collider::current_id = id + 1;
		}

		colliders[level].push_back(std::move(collider));
	}

	// get ']'
	file.get(c);
	file.ignore();
	file.ignore();

	//----------------------------------------------
	// Enemies

	// get '['
	file.get(c);

	// get the number of enemies
	file.get(cnt_buffer, 6);
	cnt = std::stoi(std::string({ cnt_buffer[1], cnt_buffer[2], cnt_buffer[3] }));

	// read enemies
	for (int i = 0; i < cnt; i++)
	{
		// get an Enemy object and then construct it from a part of buffer using initializer list
		file.get(enemies_buffer, 21);

		// (x;xxx;xxx;xxx;xx;x) <==> (level; xpos; ypos; health; step; direction)
		int level = std::stoi(std::string({ enemies_buffer[1] }));
		int xpos = std::stoi(std::string({ enemies_buffer[3], enemies_buffer[4], enemies_buffer[5] }));
		int ypos = std::stoi(std::string({ enemies_buffer[7], enemies_buffer[8], enemies_buffer[9] }));
		int health = std::stoi(std::string({ enemies_buffer[11], enemies_buffer[12], enemies_buffer[13] }));
		int step = std::stoi(std::string({ enemies_buffer[15], enemies_buffer[16] }));
		int direction = std::stoi(std::string({ enemies_buffer[18] }));

		std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(xpos, ypos);
		enemy->health = health;
		enemy->characterDirection = static_cast<Character::ECharacterDirection>(direction);
		enemy->step = step;

		enemies[level].push_back(std::move(enemy));
	}

	// get ']'
	file.get(c);
	file.ignore();
	file.ignore();

	//----------------------------------------------
	// Weapons

	// get '['
	file.get(c);

	// get the number of weapons
	file.get(cnt_buffer, 6);
	cnt = std::stoi(std::string({ cnt_buffer[1], cnt_buffer[2], cnt_buffer[3] }));

	// get the current weapon
	char curr_weapon_buffer[4];
	file.get(curr_weapon_buffer, 4);
	int curr_weapon = std::stoi(std::string({ curr_weapon_buffer[1], curr_weapon_buffer[2] }));

	// read weapons
	for (int i = 0; i < cnt; i++)
	{
		// get an Weapon object and then construct it from a part of buffer using initializer list
		file.get(weapons_buffer, 14);

		// (x;x;xxx;xxx) <==> (level; type; xpos; ypos)
		int level = std::stoi(std::string({ weapons_buffer[1] }));
		int type = std::stoi(std::string({ weapons_buffer[3] }));
		int xpos = std::stoi(std::string({ weapons_buffer[5], weapons_buffer[6], weapons_buffer[7] }));
		int ypos = std::stoi(std::string({ weapons_buffer[9], weapons_buffer[10], weapons_buffer[11] }));

		if (type == 1)
		{
			std::shared_ptr<Knife> knife = std::make_shared<Knife>(xpos, ypos);

			if (type == curr_weapon)
			{
				player->inventory->weapon = knife;
			}
			weapons[level].push_back(std::move(knife));
		}
		else if (type == 2)
		{
			std::shared_ptr<Sword> sword = std::make_shared<Sword>(xpos, ypos);
			

			if (type == curr_weapon)
			{
				player->inventory->weapon = sword;
			}
			weapons[level].push_back(std::move(sword));
		}
	}

	// get ']'
	file.get(c);
	file.ignore();
	file.ignore();

	//----------------------------------------------
	// Bonuses

	// get '['
	file.get(c);

	// get the number of enemies
	file.get(cnt_buffer, 6);
	cnt = std::stoi(std::string({ cnt_buffer[1], cnt_buffer[2], cnt_buffer[3] }));

	// read bonuses
	for (int i = 0; i < cnt; i++)
	{
		// get a Bonuses object and then construct it from a part of buffer using initializer list
		file.get(bonuses_buffer, 14);

		// (x;x;xxx;xxx) <==> (level; id; xpos; ypos)
		int level = std::stoi(std::string({ bonuses_buffer[1] }));
		int id = std::stoi(std::string({ bonuses_buffer[3] }));
		int xpos = std::stoi(std::string({ bonuses_buffer[5], bonuses_buffer[6], bonuses_buffer[7] }));
		int ypos = std::stoi(std::string({ bonuses_buffer[9], bonuses_buffer[10], bonuses_buffer[11] }));

		if (id == 0)
		{
			std::shared_ptr<Health> health = std::make_shared<Health>(xpos, ypos);
			bonuses[level].push_back(std::move(health));
		}
		else
		{
			std::shared_ptr<Gem> gem = std::make_shared<Gem>(xpos, ypos);
			gem->id = id;
			if (id > Bonus::current_id)
			{
				Bonus::current_id = id + 1;
			}
			bonuses[level].push_back(std::move(gem));
		}
	}

	// get ']'
	file.get(c);
	file.ignore();

	//----------------------------------------------

	file.close();

	map->load(map->level);
}
//-------------------------------------------------------------------------------------------------
void Game::saveGame()
{
	std::ofstream file;
	file.open("examples/saves/1.save", std::ios_base::trunc);

	//----------------------------------------------
	// Map
	file << map->level << '\n';
	for (int level = 0; level < 5; level++)
	{
		file << map->isLevelLoaded[level];
	}
	file << '\n';
	for (int level = 0; level < 5; level++)
	{
		if (map->isLevelLoaded[level])
		{
			for (int row = 0; row < MAP_HEIGHT; row++)
			{
				for (int col = 0; col < MAP_WIDTH; col++)
				{
					file << map->mapTextures[level + 1][row][col];
				}
				file << '\n';
			}
			file << '\n';
		}
	}

	//----------------------------------------------
	// Player
	file << "[(" << std::setw(3) << std::setfill('0') << player->xpos << ";"
		<< std::setw(3) << std::setfill('0') << player->ypos << ";"
		<< std::setw(3) << std::setfill('0') << player->health << ";"
		<< player->inventory->gems << ";"
		<< static_cast<int>(player->characterDirection) << ")]\n\n";

	//----------------------------------------------
	// Colliders
	int cntColliders = 0;
	for (auto& kv : colliders)
	{
		for (auto& c : kv.second)
		{
			if (c->active)
			{
				cntColliders++;
			}
		}
	}

	file << "[{" << std::setw(3) << std::setfill('0') << cntColliders << "}";

	for (auto& kv : colliders)
	{
		if (!kv.second.empty())
		{
			for (auto& c : kv.second)
			{
				if (c->active)
				{
					file << "(" << kv.first << ";" 
						<< std::setw(3) << std::setfill('0') << c->id << ";"
						<< std::setw(3) << std::setfill('0') << c->xpos << ";"
						<< std::setw(3) << std::setfill('0') << c->ypos << ")";
				}
			}
		}
	}
	file << "]\n\n";

	//----------------------------------------------
	// Enemies
	int cntEnemies = 0;
	for (auto& kv : enemies)
	{
		for (auto& e : kv.second)
		{
			if (e->active)
			{
				cntEnemies++;
			}
		}
	}

	file << "[{" << std::setw(3) << std::setfill('0') << cntEnemies << "}";

	for (auto& kv : enemies)
	{
		if (!kv.second.empty())
		{
			for (auto& e : kv.second)
			{
				if (e->active)
				{
					file << "(" << kv.first << ";"
						<< std::setw(3) << std::setfill('0') << e->xpos << ";"
						<< std::setw(3) << std::setfill('0') << e->ypos << ";"
						<< std::setw(3) << std::setfill('0') << e->health << ";"
						<< std::setw(2) << std::setfill('0') << e->step << ";"
						<< static_cast<int>(e->characterDirection) << ")";
				}
			}
		}
	}
	file << "]\n\n";

	//----------------------------------------------
	// Weapons
	int cntWeapons = 0;
	for (auto& kv : weapons)
	{
		for (auto& w : kv.second)
		{
			if (w->active)
			{
				cntWeapons++;
			}
		}
	}

	file << "[{" << std::setw(3) << std::setfill('0') << cntWeapons << "}";
	
	file << "{";
	if (player->inventory->weapon->getDamage() == KNIFE_DAMAGE)
	{
		file << "1";
	}
	else if (player->inventory->weapon->getDamage() == SWORD_DAMAGE)
	{
		file << "2";
	}
	else
	{
		file << "0";
	}
	file << "}";

	for (auto& kv : weapons)
	{
		if (!kv.second.empty())
		{
			for (auto& w : kv.second)
			{
				if (w->active)
				{
					file << "(" << kv.first << ";";

					if (w->getDamage() == KNIFE_DAMAGE)
					{
						file << "1;";
					}
					else if (w->getDamage() == SWORD_DAMAGE)
					{
						file << "2;";
					}

					file << std::setw(3) << std::setfill('0') << w->xpos << ";"
						<< std::setw(3) << std::setfill('0') << w->ypos << ")";
				}
			}
		}
	}
	file << "]\n\n";

	//----------------------------------------------
	// Bonuses
	int cntBonuses = 0;
	for (auto& kv : bonuses)
	{
		for (auto& b : kv.second)
		{
			if (b->active)
			{
				cntBonuses++;
			}
		}
	}

	file << "[{" << std::setw(3) << std::setfill('0') << cntBonuses << "}";

	for (auto& kv : bonuses)
	{
		if (!kv.second.empty())
		{
			for (auto& b : kv.second)
			{
				if (b->active)
				{
					file << "(" << kv.first << ";" << b->id << ";"
						<< std::setw(3) << std::setfill('0') << b->xpos << ";"
						<< std::setw(3) << std::setfill('0') << b->ypos << ")";
				}
			}
		}
	}
	file << "]\n";

	file.close();
}
//-------------------------------------------------------------------------------------------------
void Game::handleEventsMenu()
{
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		onMenu = false;
		onRunning = false;
		onEndGame = false;
		break;
	case SDL_KEYDOWN:
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_RETURN:
		{
			if (selectorPosition == 0)
			{
				onMenu = false;
				isLoadedFromSave = false;
			}
			else if (selectorPosition == 1)
			{
				onMenu = false;
				isLoadedFromSave = true;
			}
			else if (selectorPosition == 2)
			{
				onMenu = false;
				onRunning = false;
				onEndGame = false;
				isLoadedFromSave = false;
			}
		}
		break;
		default:
			break;
		}
	}
	break;
	default:
		break;
	}

	//continuous-response keys
	keystate = SDL_GetKeyboardState(NULL);
	if (keystate[SDL_SCANCODE_UP] || keystate[SDL_SCANCODE_W])
	{
		selectorPosition--;
		if (selectorPosition < 0)
		{
			selectorPosition = 0;
		}
	}
	else if (keystate[SDL_SCANCODE_DOWN] || keystate[SDL_SCANCODE_S])
	{
		selectorPosition++;
		if (selectorPosition > 2)
		{
			selectorPosition = 2;
		}
	}
}
//-------------------------------------------------------------------------------------------------
void Game::updateMenu()
{
	menu->update();

	if (selectorPosition == 0)
	{
		selector->xpos = 140;
		selector->ypos = 245;
	}
	else if (selectorPosition == 1)
	{
		selector->xpos = 140;
		selector->ypos = 340;
	}
	else if (selectorPosition == 2)
	{
		selector->xpos = 140;
		selector->ypos = 435;
	}

	selector->update();
}
//-------------------------------------------------------------------------------------------------
void Game::renderMenu()
{
	SDL_RenderClear(renderer);
	menu->render();
	selector->render();
	SDL_RenderPresent(renderer);
}
//-------------------------------------------------------------------------------------------------
void Game::handleEventsRunning()
{
	//single-hit keys
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
	{
		onMenu = false;
		onRunning = false;
		onEndGame = false;
		break;
	}
	case SDL_KEYDOWN:
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_F5:
			saveGame();
			break;
		case SDLK_SPACE:
		{
			std::shared_ptr<Weapon> weapon = player->inventory->weapon;
			attack->active = true;

			if (player->characterDirection == Character::ECharacterDirection::left)
			{
				attack->xpos = player->xpos - weapon->getLength() - TEXTURE_SIZE / 3;
				attack->ypos = player->ypos;

				// prepare weapon texture
				if (weapon->getDamage() == KNIFE_DAMAGE)
				{
					attack->texture = attackKnife[player->characterDirection];
				}
				else if (weapon->getDamage() == SWORD_DAMAGE)
				{
					attack->texture = attackSword[player->characterDirection];
				}
			}
			else if (player->characterDirection == Character::ECharacterDirection::right)
			{
				attack->xpos = player->xpos + weapon->getLength() + TEXTURE_SIZE / 3;
				attack->ypos = player->ypos;

				// prepare weapon texture
				if (weapon->getDamage() == KNIFE_DAMAGE)
				{
					attack->texture = attackKnife[player->characterDirection];
				}
				else if (weapon->getDamage() == SWORD_DAMAGE)
				{
					attack->texture = attackSword[player->characterDirection];
				}
			}
			else if (player->characterDirection == Character::ECharacterDirection::up)
			{
				attack->xpos = player->xpos;
				attack->ypos = player->ypos - weapon->getLength() - TEXTURE_SIZE / 2;

				// prepare weapon texture
				if (weapon->getDamage() == KNIFE_DAMAGE)
				{
					attack->texture = attackKnife[player->characterDirection];
				}
				else if (weapon->getDamage() == SWORD_DAMAGE)
				{
					attack->texture = attackSword[player->characterDirection];
				}
			}
			else if (player->characterDirection == Character::ECharacterDirection::down)
			{
				attack->xpos = player->xpos;
				attack->ypos = player->ypos + weapon->getLength() + TEXTURE_SIZE / 2;

				// prepare weapon texture
				if (weapon->getDamage() == KNIFE_DAMAGE)
				{
					attack->texture = attackKnife[player->characterDirection];
				}
				else if (weapon->getDamage() == SWORD_DAMAGE)
				{
					attack->texture = attackSword[player->characterDirection];
				}
			}
			for (auto& enemy : enemies[map->level])
			{
				if (enemy->active)
				{
					if (Collision::AABB(attack, enemy))
					{
						enemy->health -= weapon->getDamage();
					}
				}
			}
			break;
		}
		default:
			break;
		}
	}
	break;
	case SDL_KEYUP:
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_SPACE:
			attack->active = false;
			break;
		default:
			break;
		}
	}
	break;

	default:
		break;
	}

	//continuous-response keys
	keystate = SDL_GetKeyboardState(NULL);
	if (keystate[SDL_SCANCODE_LEFT] || keystate[SDL_SCANCODE_A])
	{
		attack->active = false;

		player->characterDirection = Character::ECharacterDirection::left;
		player->xpos -= PLAYER_STEP;

		// colliders
		for (auto& collider : colliders[map->level])
		{
			if (collider->active)
			{
				if (Collision::AABB(player, collider))
				{
					player->xpos += PLAYER_STEP;
				}
			}
		}
		if (player->xpos < 0)
		{
			switch (map->level)
			{
			case 2:
				map->load(1);
				player->xpos = SCREEN_WIDTH - TEXTURE_SIZE;
				break;
			case 5:
				map->load(2);
				player->xpos = SCREEN_WIDTH - TEXTURE_SIZE;
				break;
			default:
				player->xpos = 0;
				break;
			}
		}
	}
	if (keystate[SDL_SCANCODE_RIGHT] || keystate[SDL_SCANCODE_D])
	{
		attack->active = false;

		player->characterDirection = Character::ECharacterDirection::right;
		player->xpos += PLAYER_STEP;

		// colliders
		for (auto& collider : colliders[map->level])
		{
			if (collider->active)
			{
				if (Collision::AABB(player, collider))
				{
					player->xpos -= PLAYER_STEP;
				}
			}
		}

		if (player->xpos + TEXTURE_SIZE > SCREEN_WIDTH)
		{
			switch (map->level)
			{
			case 1:
				map->load(2);
				player->xpos = 0;
				break;
			case 2:
				map->load(5);
				player->xpos = 0;
				break;
			case 5:
				onRunning = false;
				break;
			default:
				player->xpos = SCREEN_WIDTH - TEXTURE_SIZE;
				break;
			}

		}
	}
	if (keystate[SDL_SCANCODE_UP] || keystate[SDL_SCANCODE_W])
	{
		attack->active = false;

		player->characterDirection = Character::ECharacterDirection::up;
		player->ypos -= PLAYER_STEP;

		// colliders
		for (auto& collider : colliders[map->level])
		{
			if (collider->active)
			{
				if (Collision::AABB(player, collider))
				{
					player->ypos += PLAYER_STEP;
				}
			}
		}

		if (player->ypos < 0)
		{
			switch (map->level)
			{
			case 2:
				map->load(3);
				player->ypos = SCREEN_HEIGHT - 2 * TEXTURE_SIZE;
				break;
			case 4:
				map->load(2);
				player->ypos = SCREEN_HEIGHT - 2 * TEXTURE_SIZE;
				break;
			default:
				player->ypos = 0;
				break;
			}
		}
	}
	if (keystate[SDL_SCANCODE_DOWN] || keystate[SDL_SCANCODE_S])
	{
		attack->active = false;

		player->characterDirection = Character::ECharacterDirection::down;
		player->ypos += PLAYER_STEP;

		//colliders
		for (auto& collider : colliders[map->level])
		{
			if (collider->active)
			{
				if (Collision::AABB(player, collider))
				{
					player->ypos -= PLAYER_STEP;
				}
			}
		}

		if (player->ypos + TEXTURE_SIZE > SCREEN_HEIGHT - TEXTURE_SIZE)
		{
			switch (map->level)
			{
			case 2:
				map->load(4);
				player->ypos = 0;
				break;
			case 3:
				map->load(2);
				player->ypos = 0;
				break;
			default:
				player->ypos = SCREEN_HEIGHT - 2 * TEXTURE_SIZE;
				break;
			}
		}
	}
}
//-------------------------------------------------------------------------------------------------
void Game::updateRunning()
{
	player->update();
	player->inventory->update();
	player->inventory->weapon->update();
	player->inventory->weapon->description->update();

	healthBar->update();

	if (attack->active)
	{
		attack->update();
	}

	//---------------------------------------------
	// enemies
	for (auto& enemy : enemies[map->level])
	{
		if (enemy->active)
		{
			enemy->update();

			if (Collision::AABB(player, enemy))
			{
				player->health -= static_cast<int>(ENEMY_DAMAGE * ENEMY_DAMAGE_COEFFICIENT);
				if (player->health <= 0)
				{
					onRunning = false;
					endGame->texture = endGame->textures["game_over"];
				}
			}
		}
	}

	//---------------------------------------------
	// weapons
	for (auto& weapon : weapons[map->level])
	{
		if (weapon->active)
		{
			if (Collision::AABB(player, weapon))
			{
				player->inventory->weapon->active = false;
				player->inventory->weapon = weapon;
				weapon->xpos = 375;
				weapon->ypos = SCREEN_HEIGHT - TEXTURE_SIZE;
				weapon->update();

				// take knife
				if (player->inventory->gems == 0)
				{
					// colliders[2] means the 2nd level map
					for (auto& collider : colliders[2])
					{
						int id = collider->id;
						if (id == 1 || id == 2 || id == 3)
						{
							collider->active = false;
						}
					}
				}
			}
		}
	}

	//---------------------------------------------
	// bonuses
	for (auto& bonus : bonuses[map->level])
	{
		if (bonus->active)
		{
			if (Collision::AABB(player, bonus))
			{
				bonus->addBonusTo(player);

				// take 1st gem
				if (bonus->id == 1)
				{
					bonus->xpos = 505;
					bonus->ypos = SCREEN_HEIGHT - TEXTURE_SIZE;
					bonus->update();

					// checking and turning off the grid to open the path to the next level
					for (auto& collider : colliders[2])
					{
						int id = collider->id;
						if (id == 7 || id == 8 || id == 9)
						{
							collider->active = false;
						}
					}

				}
				// take 2nd gem
				else if (bonus->id == 2)
				{
					bonus->xpos = 554;
					bonus->ypos = SCREEN_HEIGHT - TEXTURE_SIZE;
					bonus->update();

					// checking and turning off the grid to open the path to the next level
					for (auto& collider : colliders[2])
					{
						int id = collider->id;
						if (id == 4 || id == 5 || id == 6)
						{
							collider->active = false;
						}
					}
				}
				// take 3rd gem
				else if (bonus->id == 3)
				{
					bonus->xpos = 603;
					bonus->ypos = SCREEN_HEIGHT - TEXTURE_SIZE;
					bonus->update();

					// checking and turning off the grid to open the path to the next level
					for (auto& collider : colliders[5])
					{
						int id = collider->id;
						if (id == 10 || id == 11 || id == 12)
						{
							collider->active = false;
						}
					}
				}
				else
				{
					bonus->active = false;
				}
			}
		}
	}
}
//-------------------------------------------------------------------------------------------------
void Game::renderRunning()
{
	SDL_RenderClear(renderer);

	map->draw();

	player->render();
	player->inventory->render();
	player->inventory->weapon->render();
	player->inventory->weapon->description->render();

	healthBar->render();

	if (attack->active)
	{
		attack->render();
	}

	//---------------------------------------------
	// colliders
	for (auto& collider : colliders[map->level])
	{
		if (collider->active)
		{
			collider->render();
		}
	}

	//---------------------------------------------
	// enemies
	for (auto& enemy : enemies[map->level])
	{
		if (enemy->active)
		{
			enemy->render();
		}
	}

	//---------------------------------------------
	// weapons
	for (auto& weapon : weapons[map->level])
	{
		if (weapon->active)
		{
			weapon->render();
		}
	}

	//---------------------------------------------
	// bonuses
	for (auto& bonus : bonuses[map->level])
	{
		if (bonus->active)
		{
			bonus->render();
		}
	}

	//---------------------------------------------
	// gems
	// render 1 gem
	if (player->inventory->gems >= 1)
	{
		for (auto& bonus : bonuses[3])
		{
			if (bonus->id == 1)
			{
				bonus->render();
			}
		}
	}
	// render 1-2 gems
	if (player->inventory->gems >= 2)
	{
		for (auto& bonus : bonuses[4])
		{
			if (bonus->id == 2)
			{
				bonus->render();
			}
		}
	}
	// render 1-3 gems
	if (player->inventory->gems == 3)
	{
		for (auto& bonus : bonuses[5])
		{
			if (bonus->id == 3)
			{
				bonus->render();
			}
		}
	}
	SDL_RenderPresent(renderer);
}
//-------------------------------------------------------------------------------------------------
void Game::handleEventsEndGame()
{
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		onEndGame = false;
		break;
	case SDL_KEYDOWN:
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_RETURN:
			onEndGame = false;
			break;
		default:
			break;
		}
	}
	break;
	default:
		break;
	}
}
//-------------------------------------------------------------------------------------------------
void Game::updateEndGame()
{
	endGame->update();
}
//-------------------------------------------------------------------------------------------------
void Game::renderEndGame()
{
	SDL_RenderClear(renderer);
	endGame->render();
	SDL_RenderPresent(renderer);
}
//-------------------------------------------------------------------------------------------------
void Game::clean()
{

	menu.reset();
	selector.reset();
	player.reset();
	map.reset();
	healthBar.reset();
	attack.reset();
	endGame.reset();

	for (auto& kv : colliders)
	{
		for (auto& c : kv.second)
		{
			c.reset();
		}
	}
	for (auto& kv : enemies)
	{
		for (auto& e : kv.second)
		{
			e.reset();
		}
	}
	for (auto& kv : weapons)
	{
		for (auto& w : kv.second)
		{
			w.reset();
		}
	}
	for (auto& kv : bonuses)
	{
		for (auto& b : kv.second)
		{
			b.reset();
		}
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

}
//-------------------------------------------------------------------------------------------------
bool Game::isRunning()
{
	return onRunning;
}
//-------------------------------------------------------------------------------------------------
bool Game::isMenu()
{
	return onMenu;
}
//-------------------------------------------------------------------------------------------------
bool Game::isEndGame()
{
	return onEndGame;
}
//-------------------------------------------------------------------------------------------------

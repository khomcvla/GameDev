#include "Inventory.h"
#include "Texture.h"
#include "Vars.h"

//-------------------------------------------------------------------------------------------------
Inventory::Inventory() : Object(0, SCREEN_HEIGHT - INVENTORY_HEIGHT)
{
	texture = Texture::loadTexture("examples/ui/inventory.png");
	gems = 0;
	weapon = std::make_shared<Weapon>(375, SCREEN_HEIGHT - TEXTURE_SIZE);
}
//-------------------------------------------------------------------------------------------------
void Inventory::update()
{
	srcRect.h = INVENTORY_HEIGHT;
	srcRect.w = INVENTORY_WIDTH;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = 0;
	destRect.y = SCREEN_HEIGHT - INVENTORY_HEIGHT;
	destRect.h = srcRect.h;
	destRect.w = srcRect.w;
}
//-------------------------------------------------------------------------------------------------
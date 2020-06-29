#include "Menu.h"
#include "Texture.h"
#include "Vars.h"

//-------------------------------------------------------------------------------------------------
Menu::Menu(int x, int y) : Object(x, y)
{
	texture = Texture::loadTexture("examples/screen/menu.png");
}
//-------------------------------------------------------------------------------------------------
void Menu::update()
{
	srcRect.h = SCREEN_HEIGHT;
	srcRect.w = SCREEN_WIDTH;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.h = srcRect.h;
	destRect.w = srcRect.w;
}
//-------------------------------------------------------------------------------------------------
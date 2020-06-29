#include "Collider.h"
#include "Texture.h"
#include "Vars.h"

#include <iostream>

int Collider::current_id = 1;
//-------------------------------------------------------------------------------------------------
Collider::Collider(int x, int y, bool isGrid) : Object(x, y)
{
	if (isGrid)
	{
		id = Collider::current_id;
		texture = Texture::loadTexture("examples/map/grid.png");
		Collider::current_id++;
	}
}
//-------------------------------------------------------------------------------------------------
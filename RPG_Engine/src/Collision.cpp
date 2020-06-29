#include "Collision.h"
#include "Vars.h"

//-------------------------------------------------------------------------------------------------
bool Collision::AABB(const std::shared_ptr<Object>& objA, const std::shared_ptr<Object>& objB)
{
	if (objA->xpos + TEXTURE_SIZE > objB->xpos &&
		objB->xpos + TEXTURE_SIZE > objA->xpos &&
		objA->ypos + TEXTURE_SIZE > objB->ypos &&
		objB->ypos + TEXTURE_SIZE > objA->ypos)
	{
		return true;
	}
	return false;
}
//-------------------------------------------------------------------------------------------------
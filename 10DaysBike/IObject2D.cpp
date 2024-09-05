#include "IObject2D.h"

bool IObject2D::GetIsOffingScreen()
{
	return GetIsOffingScreen(pos_);
}

bool IObject2D::GetIsOffingScreen(const Vec2& pos)
{
	bool isOffingX = (pos.x > WINDOW_SIZE.x) || (pos.x < 0);
	bool isOffingY = (pos.y > WINDOW_SIZE.y) || (pos.y < 0);

	return (isOffingX || isOffingY);
}

bool IObject2D::GetIsOffingScreen(const Vec2& pos, const Vec2& pos2)
{
	return (GetIsOffingScreen(pos) && GetIsOffingScreen(pos2));
}

bool IObject2D::GetIsOffingScreen(const Vec2& pos, const Vec2& pos2, const Vec2& pos3)
{
	return (GetIsOffingScreen(pos) && GetIsOffingScreen(pos2) && GetIsOffingScreen(pos3));
}

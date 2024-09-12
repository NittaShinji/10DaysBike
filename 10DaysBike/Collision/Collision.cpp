#include "Collision.h"

Collision::Collision() {}
Collision::~Collision() {}

bool Collision::CheckCircle2Circle(const Circle& circleA, const Circle& circleB)
{
	//‹——£‚ðŒvŽZ
    Vec2 cal;
    cal.x = circleA.pos.x - circleB.pos.x;
    cal.y = circleA.pos.y - circleB.pos.y;
    float distance = sqrt(cal.x * cal.x + cal.y * cal.y);

	if (distance <= circleA.radius + circleB.radius)
	{
		return true;
	}
	
    return false;
}

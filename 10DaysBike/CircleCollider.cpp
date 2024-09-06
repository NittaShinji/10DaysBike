#include "CircleCollider.h"

const float CircleCollider::kDefaultRadius_ = 1.0f;
const Vec2 CircleCollider::kDefaultOffset_ = { 0.0f,0.0f };

void CircleCollider::Update()
{
	//‰~‚Ìƒƒ“ƒo•Ï”‚ğXV
	Circle::radius = radius;
	Circle::pos = pos;
}
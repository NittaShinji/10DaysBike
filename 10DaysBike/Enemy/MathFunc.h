#pragma once
#include"Vec2.h"
const float PI = 3.14159265359f;
const float DEG_TO_RAD = PI / 180.0f;
const float RAD_TO_DEG = 180.0f / PI;

namespace MathFunc {
	float DeltaAngle(float angle1, float angle2);
	Vec2 AngleToVector(float angleInDegrees);
}
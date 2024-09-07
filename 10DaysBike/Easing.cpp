#include "Easing.h"

static const float PI = 3.1415f;


float Lerp(float v1, float v2, float t)
{
	return v1 + t * (v2 - v1);
}

Vec2 LerpVec2(const Vec2& v1, const Vec2& v2, float t)
{
	return v1 + t * (v2 - v1);
}

float EaseIn(float t)
{
	return 1 - cos((t * PI) / 2.0f);
}

float EaseOut(float t)
{
	return sin((t * PI) / 2.0f);
}

float EaseInOutBack(float t)
{
	const float C1 = 1.70158f;
	const float C2 = C1 * 1.525f;

	const float RATIO_MAX = 1.0f;

	return t < 0.5f
		? (powf(2.0f * t, 2.0f) * ((C2 + RATIO_MAX) * 2.0f * t - C2)) / 2.0f
		: (powf(2.0f * t - 2.0f, 2.0f) * ((C2 + RATIO_MAX) * (t * 2.0f - 2.0f) + C2) + 2.0f) / 2.0f;
}

float EaseInOut(float t)
{
	return t == 0.0f
		? 0.0f
		: t == 1.0f
		? 1.0f
		: t < 0.5f ? powf(2, 20.0f * t - 10.0f) / 2.0f
		: (2.0f - powf(2.0f, -20 * t + 10.0f)) / 2.0f;
}
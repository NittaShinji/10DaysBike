#pragma once
#include<math.h>
#include"Vec2.h"

float Lerp(float v1, float v2, float t);

Vec2 LerpVec2(const Vec2& v1, const Vec2& v2, float t);

float EaseIn(float t);

float EaseOut(float t);

float EaseInOutBack(float t);

float EaseInOut(float t);

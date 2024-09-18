#pragma once
#include<math.h>
#include"Vec2.h"

/// <summary>
/// イージング情報
/// 初期位置
/// 終点までの距離
/// アニメーションの現在の時間
/// アニメーションが行われる時間
/// </summary>
typedef struct EasingInfo
{
	//初期位置
	float startPos;
	//終点までの距離
	float endDistance;
	//アニメーションの現在の時間
	float time;
	//アニメーションが行われる時間
	const float totalTime;

} EasingInfo;

float Lerp(float v1, float v2, float t);

Vec2 LerpVec2(const Vec2& v1, const Vec2& v2, float t);

float EaseIn(float t);

float EaseOut(float t);

float EaseInOutBack(float t);

float EaseInOut(float t);

float EaseOutQuint(float x);

float PlayEaseOutQuint(EasingInfo easingInfo);

float PlayEaseOutQuint(float startPos, float endDistance, float time, float totalTime);

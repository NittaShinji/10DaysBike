#pragma once 
#include "Vec2.h"

///<summary>
/// 衝突判定の形状を定義する
///</summary>

///<summary>
/// 円
///</summary>
struct Circle
{
	//中心座標
	const Vec2 kDefaultCenter = { 0.0f,0.0f};
	Vec2 center = kDefaultCenter;

	const float kDefaultUpVec = 1.0f;
	float upVec = kDefaultUpVec;

	//半径
	const float kDefaultCircleRadius = 1.0f;
	float radius = kDefaultCircleRadius;

	const Vec2 kDefaultPos = { 0.0f,0.0f};
	Vec2 pos = kDefaultPos;
};

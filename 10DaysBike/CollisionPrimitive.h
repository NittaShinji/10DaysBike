#pragma once 
#include "Vec2.h"

///<summary>
/// �Փ˔���̌`����`����
///</summary>

///<summary>
/// �~
///</summary>
struct Circle
{
	//���S���W
	const Vec2 kDefaultCenter = { 0.0f,0.0f};
	Vec2 center = kDefaultCenter;

	const float kDefaultUpVec = 1.0f;
	float upVec = kDefaultUpVec;

	//���a
	const float kDefaultCircleRadius = 1.0f;
	float radius = kDefaultCircleRadius;

	const Vec2 kDefaultPos = { 0.0f,0.0f};
	Vec2 pos = kDefaultPos;
};

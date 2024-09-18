#pragma once
#include<math.h>
#include"Vec2.h"

/// <summary>
/// �C�[�W���O���
/// �����ʒu
/// �I�_�܂ł̋���
/// �A�j���[�V�����̌��݂̎���
/// �A�j���[�V�������s���鎞��
/// </summary>
typedef struct EasingInfo
{
	//�����ʒu
	float startPos;
	//�I�_�܂ł̋���
	float endDistance;
	//�A�j���[�V�����̌��݂̎���
	float time;
	//�A�j���[�V�������s���鎞��
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

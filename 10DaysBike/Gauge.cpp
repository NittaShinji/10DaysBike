#include "Gauge.h"
#include "Easing.h"

const ColorDxLib Gauge::COLOR = { 0,195,195 };
const ColorDxLib Gauge::DANGER_COLOR = { 255,50,50 };


void Gauge::Init()
{
	color_ = COLOR;
}

void Gauge::Update()
{
}

void Gauge::Draw()
{
	const float RATIO = EaseIn(1.0f - ratio_);

	color_ = { (uint8_t)Lerp(COLOR.r,DANGER_COLOR.r,RATIO),
		(uint8_t)Lerp(COLOR.g,DANGER_COLOR.g,RATIO),
		(uint8_t)Lerp(COLOR.b,DANGER_COLOR.b,RATIO) };

	DrawBox(pos_.x, pos_.y, pos_.x + widthHeight_.x, pos_.y + widthHeight_.y,
		GetColorUsedForDrawing(), true);
}

#include "Gauge.h"
#include "Easing.h"

const ColorDxLib IGauge::COLOR = { 255,255,255 };
const ColorDxLib IGauge::DANGER_COLOR = { 255,20,20 };


void IGauge::Init()
{
	color_ = COLOR;
}

void IGauge::Update()
{
}

void IGauge::Draw()
{
	const float RATIO = EaseIn(1.0f - colorRatio_);

	color_ = { (uint8_t)Lerp(COLOR.r,DANGER_COLOR.r,RATIO),
		(uint8_t)Lerp(COLOR.g,DANGER_COLOR.g,RATIO),
		(uint8_t)Lerp(COLOR.b,DANGER_COLOR.b,RATIO) };

	DrawProcess();
}


void IGauge::DrawProcess()
{
	DrawBox(pos_.x, pos_.y, pos_.x + widthHeight_.x, pos_.y + widthHeight_.y,
		GetColorUsedForDrawing(), true);
}
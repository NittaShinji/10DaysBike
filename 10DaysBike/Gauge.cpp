#include "Gauge.h"

const ColorDxLib Gauge::PROT_COLOR = { 100,255,0 };


void Gauge::Init()
{
	color_ = PROT_COLOR;
}

void Gauge::Update()
{
}

void Gauge::Draw()
{
	DrawBox(pos_.x, pos_.y, pos_.x + widthHeight_.x, pos_.y + widthHeight_.y,
		GetColorUsedForDrawing(), true);
}

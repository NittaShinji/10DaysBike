#include "GaugeFrame.h"

const ColorDxLib GaugeFrame::COLOR = { 110,110,110 };

void GaugeFrame::Init()
{
	color_ = COLOR;
}

void GaugeFrame::Update()
{

}

void GaugeFrame::Draw()
{
	const float LEFT = pos_.x - widthHeight_.x / 2.0f   + thickness_ / 2.0f;
	const float RIGHT = pos_.x + widthHeight_.x / 2.0f  - thickness_ / 2.0f;
	const float TOP = pos_.y - widthHeight_.y / 2.0f    + thickness_ / 2.0f;
	const float BOTTOM = pos_.y + widthHeight_.y / 2.0f - thickness_ / 2.0f;

	//è„ïî
	DrawLine(LEFT, TOP, RIGHT, TOP, GetColorUsedForDrawing(), thickness_);
	//ç∂
	DrawLine(LEFT, TOP, LEFT, BOTTOM, GetColorUsedForDrawing(), thickness_);
	//âE
	DrawLine(RIGHT, TOP, RIGHT, BOTTOM, GetColorUsedForDrawing(), thickness_);
	//â∫
	DrawLine(LEFT, BOTTOM, RIGHT, BOTTOM, GetColorUsedForDrawing(), thickness_);
}

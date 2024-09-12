#include "DecreGauge.h"
#include "Easing.h"

const ColorDxLib DecreGauge::COLOR = { 200,200,200 };
const float DecreGauge::ALPHA = 180.0f;

void DecreGauge::Init()
{
	color_ = COLOR;
}

void DecreGauge::Update()
{
	if (isDecreacing_)
	{
		decreTimer_++;

		float t = decreTimer_ / (float)decreTimerTmp_;

		widthHeight_ = LerpVec2(sWidthHeight_, eWidthHeight_, EaseIn(t));

		if (t >= 1.0f)
		{
			isDecreacing_ = false;
		}
	}
}

void DecreGauge::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, ALPHA);

	IGauge::DrawProcess();

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void DecreGauge::StartDecreGauge(const Vec2& endWidthHeight, uint16_t time)
{
	//“r’†‚Å‚Ü‚½ŒÄ‚Î‚ê‚½‚çˆø‚«Œp‚®‚½‚ß
	if (! isDecreacing_)
	{
		sWidthHeight_ = widthHeight_;
	}

	decreTimer_ = 0;

	eWidthHeight_ = endWidthHeight;

	decreTimerTmp_ = time;

	isDecreacing_ = true;
}

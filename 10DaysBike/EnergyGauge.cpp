#include "EnergyGauge.h"

void EnergyGauge::Init()
{
	gauge_ = std::make_unique<Gauge>();
	gauge_->Init();

	frame_ = std::make_unique<GaugeFrame>();
	frame_->Init();

	frame_->SetPos({ (float)(FRAME_LEFT + FRAME_WIDTH / 2) ,(float)(FRAME_TOP + FRAME_HEIGHT / 2) });

	gaugeRatio_ = 1.0f;
}

void EnergyGauge::Update()
{
	frameScaleRate_ += (0.0f - frameScaleRate_) * CHARGE_SCALING_DECRE;

	Vec2 gaugeWH = Vec2{ gaugeWidthHeight_.x * gaugeRatio_, gaugeWidthHeight_.y };
	gauge_->SetWidthHeight(gaugeWH + gaugeWH * frameScaleRate_);
	gauge_->SetRatio(gaugeRatio_);

	gauge_->SetPos({ (float)GAUGE_LEFT - FRAME_WIDTH / 2.0f * frameScaleRate_
		, (float)GAUGE_TOP - FRAME_HEIGHT / 2.0f * frameScaleRate_ });

	frame_->SetWidthHeight(frameWidthHeight_ + frameWidthHeight_ * frameScaleRate_);
	frame_->SetThickness(frameThickness + frameThickness * frameScaleRate_);

	gauge_->Update();
	frame_->Update();
}

void EnergyGauge::Draw()
{
	gauge_->Draw();
	frame_->Draw();
}

bool EnergyGauge::DecreGaugeRatio(float ratio)
{
	bool ans = false;

	if (gaugeRatio_ > 0.0f)
	{
		gaugeRatio_ = max(gaugeRatio_ - ratio, 0);
		ans = true;
	}

	return ans;
}

bool EnergyGauge::ChargeGaugeRatio(float posY, float ratio)
{
	if (posY >= FRAME_TOP)
	{
		gaugeRatio_ = min(gaugeRatio_ + ratio, 1.0f);

		frameScaleTime_ += CHARGE_SCALING_INCRE;
		frameScaleRate_ = sinf(frameScaleTime_) * CHARGE_SCALING_MAX;
		return true;
	}
	return false;
}

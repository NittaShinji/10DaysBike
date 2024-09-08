#include "EnergyGauge.h"

void EnergyGauge::Init()
{
	gauge_ = std::make_unique<Gauge>();
	gauge_->Init();

	frame_ = std::make_unique<GaugeFrame>();
	frame_->Init();

	gauge_->SetPos({ (float)GAUGE_LEFT, (float)GAUGE_TOP });

	frame_->SetPos({ (float)(FRAME_LEFT + FRAME_WIDTH / 2) ,(float)(FRAME_TOP + FRAME_HEIGHT / 2) });

	gaugeRatio_ = 1.0f;
}

void EnergyGauge::Update()
{
	gauge_->SetWidthHeight({ gaugeWidthHeight_.x * gaugeRatio_,gaugeWidthHeight_.y });
	frame_->SetWidthHeight(frameWidthHeight_);
	frame_->SetThickness(frameThickness);

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
		gaugeRatio_ -= (ratio);
		ans = true;
	}

	return ans;
}

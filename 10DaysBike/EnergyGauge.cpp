#include "EnergyGauge.h"

const float EnergyGauge::DECRE_GAUGE_INTERVAL = 0.05f;


Vec2 EnergyGauge::GetGaugeWidthHeight()
{
	Vec2 gaugeWH = Vec2{ gaugeWidthHeight_.x * gaugeRatio_, gaugeWidthHeight_.y };
	return gaugeWH + gaugeWH * frameScaleRate_;
}

void EnergyGauge::Init()
{
	gaugeRatio_ = 1.0f;

	gauge_ = std::make_unique<IGauge>();
	gauge_->Init();

	decreGauge_ = std::make_unique<DecreGauge>();
	decreGauge_->Init();
	decreGauge_->SetStartWH(GetGaugeWidthHeight());

	frame_ = std::make_unique<GaugeFrame>();
	frame_->Init();

	frame_->SetPos({ (float)(FRAME_LEFT + FRAME_WIDTH / 2) ,(float)(FRAME_TOP + FRAME_HEIGHT / 2) });


	damagedShake_ = std::make_unique<Shake>();
}

void EnergyGauge::Update()
{
	frameScaleRate_ += (-frameScaleRate_) * CHARGE_SCALING_DECRE;

	//ゲージ内部
	gauge_->SetWidthHeight(GetGaugeWidthHeight());
	gauge_->SetColorRatio(gaugeRatio_);
	gauge_->SetPos({
		(float)GAUGE_LEFT - FRAME_WIDTH / 2.0f * frameScaleRate_
		+ damagedShake_->GetShake()
		, (float)GAUGE_TOP - FRAME_HEIGHT / 2.0f * frameScaleRate_
		+ damagedShake_->GetShake()
		});

	//減るのがわかりやすきゲージ
	decreGauge_->SetPos(gauge_->GetPos());

	//枠
	frame_->SetWidthHeight(frameWidthHeight_ + frameWidthHeight_ * frameScaleRate_);
	frame_->SetThickness(frameThickness + frameThickness * frameScaleRate_);
	frame_->SetPos({ 
		(float)(FRAME_LEFT + FRAME_WIDTH / 2) + damagedShake_->GetShake() ,
		(float)(FRAME_TOP + FRAME_HEIGHT / 2) + damagedShake_->GetShake()
		});


	//更新処理
	gauge_->Update();
	decreGauge_->Update();
	frame_->Update();

	damagedShake_->Update();


	//
	if (decreGaugeInterval_ < 0)
	{
		decreGauge_->StartDecreGauge(GetGaugeWidthHeight(), DECRE_GAUGE_TIME);
		decreGaugeInterval_ = DECRE_GAUGE_INTERVAL;
	}
}

void EnergyGauge::Draw()
{
	decreGauge_->Draw();
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

		//一定の数値減ったら後ろのゲージも動かす
		decreGaugeInterval_ -= ratio;
	}

	return ans;
}

bool EnergyGauge::DamageDecreGauge(float ratio)
{
	gaugeRatio_ = max(gaugeRatio_ - ratio, 0);

	damagedShake_->BeginShake(DAMAGED_SHAKE_TIME, DAMAGED_SHAKE_MAX);

	if (gaugeRatio_ <= 0)
	{
		return false;
	}

	return true;
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

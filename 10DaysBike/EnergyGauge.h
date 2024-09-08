#pragma once
#include"IObject2D.h"
#include"Gauge.h"
#include"GaugeFrame.h"

//画面下のゲージ
class EnergyGauge
{
public:
	//ゲージ枠の長さ
	const uint16_t FRAME_WIDTH = WINDOW_SIZE.x;
	const uint16_t FRAME_HEIGHT = WINDOW_SIZE.y / 8;
	//ゲージの枠の太さ
	const uint16_t FRAME_THICKNESS = WINDOW_SIZE.x / 20 / 2;
	//ゲージ枠の位置
	const uint16_t FRAME_TOP = WINDOW_SIZE.y - FRAME_HEIGHT;
	const uint16_t FRAME_LEFT = 0;

	//ゲージ本体の長さ
	const uint16_t GAUGE_WIDTH = FRAME_WIDTH - FRAME_THICKNESS * 2;
	const uint16_t GAUGE_HEIGHT = FRAME_HEIGHT - FRAME_THICKNESS * 2;
	//左端からのゲージ本体距離
	const uint16_t GAUGE_LEFT = FRAME_LEFT + FRAME_THICKNESS;
	//上部からの
	const uint16_t GAUGE_TOP = FRAME_TOP + FRAME_THICKNESS;

private:
	Vec2 frameWidthHeight_ = { (float)FRAME_WIDTH, (float)FRAME_HEIGHT };
	Vec2 gaugeWidthHeight_ = { (float)GAUGE_WIDTH, (float)GAUGE_HEIGHT };
	float frameThickness = FRAME_THICKNESS;

	float gaugeRatio_ = 1.0f;

	std::unique_ptr<Gauge> gauge_ = nullptr;
	std::unique_ptr<GaugeFrame> frame_ = nullptr;


private:


public:
	void Init();
	void Update();
	void Draw();
public:
	bool DecreGaugeRatio(float ratio);
};


#pragma once
#include"IObject2D.h"
#include"Gauge.h"
#include"GaugeFrame.h"

//��ʉ��̃Q�[�W
class EnergyGauge
{
public:
	//�Q�[�W�g�̒���
	const uint16_t FRAME_WIDTH = WINDOW_SIZE.x - UI_SIZE.x;
	const uint16_t FRAME_HEIGHT = WINDOW_SIZE.y / 8;
	//�Q�[�W�̘g�̑���
	const uint16_t FRAME_THICKNESS = (GAME_WINDOW_SIZE.x) / 20 / 2;
	//�Q�[�W�g�̈ʒu
	const uint16_t FRAME_TOP = WINDOW_SIZE.y - FRAME_HEIGHT;
	const uint16_t FRAME_LEFT = UI_SIZE.x;

	//�Q�[�W�{�̂̒���
	const uint16_t GAUGE_WIDTH = FRAME_WIDTH - FRAME_THICKNESS * 2;
	const uint16_t GAUGE_HEIGHT = FRAME_HEIGHT - FRAME_THICKNESS * 2;
	//���[����̃Q�[�W�{�̋���
	const uint16_t GAUGE_LEFT = FRAME_LEFT + FRAME_THICKNESS;
	//�㕔�����
	const uint16_t GAUGE_TOP = FRAME_TOP + FRAME_THICKNESS;
public:
	//
	const float CHARGE_SCALING_MAX = 0.03f;
	const float CHARGE_SCALING_INCRE = 0.234f;
	const float CHARGE_SCALING_DECRE = 0.023f;


private:
	Vec2 frameWidthHeight_ = { (float)FRAME_WIDTH, (float)FRAME_HEIGHT };
	Vec2 gaugeWidthHeight_ = { (float)GAUGE_WIDTH, (float)GAUGE_HEIGHT };
	float frameThickness = FRAME_THICKNESS;

	float gaugeRatio_ = 1.0f;

	float frameScaleRate_ = 0;
	float frameScaleTime_ = 0;

	std::unique_ptr<Gauge> gauge_ = nullptr;
	std::unique_ptr<GaugeFrame> frame_ = nullptr;


private:


public:
	void Init();
	void Update();
	void Draw();
public:
	bool DecreGaugeRatio(float ratio);
	bool ChargeGaugeRatio(float posY, float ratio);
};


#pragma once
#include"Trajectories.h"

//�������̃`���[�W���̋O�Ղ̔z��
class ChargeTrajectories : public Trajectories
{
public:
	static const float CHARGE_MOVE_RATE;
	static const float CHARGE_MOVE_WIDTH;
private:
	float timer_ = 0;
	float timerAdd_ = 0;


private:
	void ChargeMoveProcess();
public:
	void Init()override;
	void Update()override;
	void Update(float dirY, std::function<bool(float trajPos, float chargeGaugeRatio)> chargeGaugeFunc);
};


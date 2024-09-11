#include "ChargeTrajectories.h"
#include "Easing.h"

const float ChargeTrajectories::CHARGE_MOVE_RATE = 0.33f;
const float ChargeTrajectories::CHARGE_MOVE_WIDTH = WINDOW_SIZE.x / 80.0f;


void ChargeTrajectories::Init()
{
}

void ChargeTrajectories::Update()
{
	Update(0, nullptr);
}

void ChargeTrajectories::Update(float dirY, std::function<bool(float trajPos, float chargeGaugeRatio)> chargeGaugeFunc)
{
	//�`���[�W�ۂ����˂��˂�����
	ChargeMoveProcess();

	Trajectories::UpdatePos(dirY, chargeGaugeFunc);

	//�n�_����ɏo���O�Ղ̏I�_��
	Trajectories::StartPosProcess();

	//�폜
	Trajectories::DeleteDeadTrajectories();
}

void ChargeTrajectories::ChargeMoveProcess()
{
	timer_++;

	for (auto& traj : trajectories_)
	{
		const float POS_Y = traj->GetTwoPoses().ePos.y;

		const float POS_Y_RATIO = (POS_Y / WINDOW_SIZE.y) * 2.0f;

		traj->SetVec({
			(sinf(timer_ * POS_Y_RATIO)) /** CHARGE_MOVE_RATE*/ * CHARGE_MOVE_WIDTH + POS_Y_RATIO
			,traj->GetScrollVec().y
			});
	}
}

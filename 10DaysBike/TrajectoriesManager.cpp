#include "TrajectoriesManager.h"
#include "KeyboardInput.h"

const float TrajectoriesManager::TRAJ_SPEED = 30.0f;
const std::string TrajectoriesManager::UP_TRAJ_NAME = "UpTraj";
const std::string TrajectoriesManager::DOWN_TRAJ_NAME = "DownTraj";
const std::string TrajectoriesManager::BURST_UP_NAME = "burstUp";
const std::string TrajectoriesManager::BURST_DOWN_NAME = "burstDown";

void TrajectoriesManager::Init()
{
	Init({ 0,0 });
}

void TrajectoriesManager::Init(const Vec2& pos)
{
	pos_ = pos;
	oldPos_ = pos_;

	trajectoriesArray_.clear();
	color_ = COLOR_DEBUG;
}

bool TrajectoriesManager::GenerateUpdate(const TrajGenerateInform& geneInfo, std::function<bool(float decreGauge, int32_t continueNum)> shootGaugeFunc)
{
	bool isDanger = GenerateTrajectory(geneInfo, shootGaugeFunc);
	oldPos_ = pos_;

	return isDanger;
}

void TrajectoriesManager::SetNewestTrajPos()
{
	if (trajectoriesArray_.size())
	{
		auto& newTrajs = trajectoriesArray_.back();
		if (newTrajs)
		{
			newTrajs->SetNewestTrajStartPos(pos_);
		}
	}
}

void TrajectoriesManager::Update()
{
	TrajGenerateInform info;
	Update(info, nullptr, nullptr);
}

bool TrajectoriesManager::Update(const TrajGenerateInform& geneInfo, std::function<bool(float decreGauge, int32_t continueNum)> shootGaugeFunc,
	std::function<bool(float trajPos, float chargeGaugeRatio)> chargeGaugeFunc)
{
	const Vec2 TRAJ_VEC = Vec2(0, geneInfo.dirY).GetNormalize() * TRAJ_SPEED;

	//1�t���[�����Ƃɐ������邽��
	bool isDanger = GenerateUpdate(geneInfo, shootGaugeFunc);

	//�ړ��ȂǍX�V����
	for (auto itr = trajectoriesArray_.begin(); itr != trajectoriesArray_.end(); itr++)
	{
		//�X�V
		itr->get()->Update(TRAJ_VEC.y, chargeGaugeFunc);

	}

	//��ԐV�����O�Ղ̈ʒu���Ǘ��N���X�ƈꏏ�ɂ���
	SetNewestTrajPos();

	for (auto itr = trajectoriesArray_.begin(); itr != trajectoriesArray_.end(); itr++)
	{
		//�����Ă�t���O�������ĂȂ��O�Ղ̔z�����������
		if (itr->get()->GetIsAlive() == false)
		{
			trajectoriesArray_.erase(itr);

			if (trajectoriesArray_.size() < 1)
			{
				break;
			}

			itr = trajectoriesArray_.begin();
		}
	}


	return isDanger;
}

void TrajectoriesManager::Draw()
{
	for (auto& trajs : trajectoriesArray_)
	{
		trajs->Draw();
	}


#ifdef _DEBUG
	DrawCircle(pos_.x, pos_.y, IObject2D::GetColorUsedForDrawing(), 10);
#endif // _DEBUG

}

void TrajectoriesManager::ProccesingNewTrajs()
{
	isNewTrajs_ = true;
}

//------------------------------------------------------------------------------------
bool TrajectoriesManager::GenerateTrajectory(const TrajGenerateInform& geneInfo,
	std::function<bool(float decreGauge, int32_t continueNum)> shootGaugeFunc)
{
	//1�̋O�Ղ̂������傤�Ƃ��̍������Ɖ��񂷂邩�𑗂�A�\�������猂����
	if (shootGaugeFunc(Trajectory::SHOOT_DECREMENT_GAUGE * geneInfo.trajCostRate,
		geneInfo.continueNum))
	{
		bool isHead = false;
		std::unique_ptr<Trajectories> trajectories = nullptr;
		//�^�[�������玟�̋O�Ղ�擪�ɂ��邽�ߐV���Ȕz�������
		if (isNewTrajs_ || trajectoriesArray_.size() == 0)
		{
			isHead = true;
			isNewTrajs_ = false;

			//�������Ă�Ƃ��̓`���[�W�p��
			if (geneInfo.dirY > 0)
			{
				trajectories = std::make_unique<ChargeTrajectories>();
			}
			else
			{
				trajectories = std::make_unique<Trajectories>();
			}
			trajectories->Init();
		}
		//�O�Ղ̔z�񂪂��łɂ����ă^�[�����ĂȂ��Ƃ�
		else
		{
			trajectories = std::move(trajectoriesArray_.back());
			trajectoriesArray_.pop_back();
		}

		//��U,���ňړ��ʂ����̂܂܃x�N�g���Ɏg��
		const Vec2 DIR_VEC = oldPos_ - pos_;

		//����y�����������O�Ղ𐶐�
		auto traj = std::make_unique<Trajectory>();
		traj->Init({ pos_,oldPos_ }, Vec2{ 0,geneInfo.dirY },
			isHead);
		//���������Q�[�W���Z�b�g
		traj->SetThickNessRate(geneInfo.trajThickRate);
		traj->SetChargeGaugeRate(geneInfo.trajCostRate);
		traj->SetName(geneInfo.name);

		//�z��ɒǉ�
		trajectories->PushBackTraj(std::move(traj));

		//�O�Քz���z��ɒǉ�
		trajectoriesArray_.push_back(std::move(trajectories));

		return true;
	}

	return false;
}

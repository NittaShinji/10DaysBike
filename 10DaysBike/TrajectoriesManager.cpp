#include "TrajectoriesManager.h"
#include "KeyboardInput.h"

const float TrajectoriesManager::TRAJ_SPEED = 24.0f;


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

void TrajectoriesManager::GenerateUpdate(const TrajGenerateInform& geneInfo, std::function<bool(float decreGauge)> shootGaugeFunc)
{
	GenerateTrajectory(geneInfo, shootGaugeFunc);
	oldPos_ = pos_;
}

void TrajectoriesManager::SetNewestTrajPos()
{
	if (trajectoriesArray_.size())
	{
		auto& newTrajs = trajectoriesArray_.back();
		if (newTrajs)
		{
			newTrajs->SetNewestTrajSPos(pos_);
		}
	}
}

void TrajectoriesManager::Update()
{
	TrajGenerateInform info;
	Update(info, nullptr, nullptr);
}

void TrajectoriesManager::Update(const TrajGenerateInform& geneInfo, std::function<bool(float decreGauge)> shootGaugeFunc,
	std::function<bool(float trajPos, float chargeGaugeRatio)> chargeGaugeFunc)
{
	const Vec2 TRAJ_VEC = Vec2(0, geneInfo.dirY).GetNormalize() * TRAJ_SPEED;

	//1�t���[�����Ƃɐ������邽��
	GenerateUpdate(geneInfo, shootGaugeFunc);

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
void TrajectoriesManager::GenerateTrajectory(const TrajGenerateInform& geneInfo,
	std::function<bool(float decreGauge)> shootGaugeFunc)
{
	if (shootGaugeFunc(Trajectory::SHOOT_DECREMENT_GAUGE * geneInfo.trajCostRate))
	{
		bool isHead = false;
		std::unique_ptr<Trajectories> trajectories = nullptr;
		//�^�[�������玟�̋O�Ղ�擪�ɂ��邽�ߐV���Ȕz�������
		if (isNewTrajs_ || trajectoriesArray_.size() == 0)
		{
			isHead = true;
			isNewTrajs_ = false;

			trajectories = std::make_unique<Trajectories>();
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

		//�z��ɒǉ�
		trajectories->PushBackTraj(std::move(traj));

		//�O�Քz���z��ɒǉ�
		trajectoriesArray_.push_back(std::move(trajectories));
	}
}

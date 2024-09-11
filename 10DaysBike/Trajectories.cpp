#include "Trajectories.h"


void Trajectories::Init()
{
}

void Trajectories::UpdatePos(float dirY, std::function<bool(float trajPos, float chargeGaugeRatio)> chargeGaugeFunc)
{
	for (auto itr = trajectories_.begin(); itr != trajectories_.end(); itr++)
	{
		//�X�V
		itr->get()->SetScrollVec({ itr->get()->GetScrollVec().x,(dirY) * 0.34f });
		itr->get()->Update(chargeGaugeFunc);
	}
}

void Trajectories::StartPosProcess()
{
	for (auto itr = trajectories_.begin(); itr != trajectories_.end(); itr++)
	{
		//��(�������V����)�̋O��
		auto nextTrajItr = itr;
		nextTrajItr++;

		if (nextTrajItr == trajectories_.end())
		{
			break;
		}

		if (itr != trajectories_.begin())
		{
			//���ɏo���O�Ղ̌��̓_���n�_�Ƃ���
			itr->get()->SetTwoPoses(
				nextTrajItr->get()->GetTwoPoses().ePos,
				itr->get()->GetTwoPoses().ePos);
		}

	}
}

void Trajectories::DeleteDeadTrajectories()
{
	for (auto itr = trajectories_.begin(); itr != trajectories_.end(); itr++)
	{
		//�����Ă�t���O�������ĂȂ��O�Ղ���������
		if (itr->get()->GetIsAlive() == false)
		{
			trajectories_.erase(itr);

			//�v�f��0�ɂȂ����玩����z�񂩂�����Ă��炤����
			if (trajectories_.size() < 1)
			{
				isAlive_ = false;
				break;
			}

			itr = trajectories_.begin();
		}
	}
}

void Trajectories::Update()
{
	Update(0, nullptr);
}

void Trajectories::Update(float dirY, std::function<bool(float trajPos, float chargeGaugeRatio)> chargeGaugeFunc)
{
	//�ړ��ȂǍX�V����
	UpdatePos(dirY, chargeGaugeFunc);

	//��ɏo�����̏I�_���n�_��
	StartPosProcess();

	//�폜
	DeleteDeadTrajectories();
}

void Trajectories::Draw()
{
	for (auto& trajs : trajectories_)
	{
		trajs->Draw();
	}
}

void Trajectories::SetNewestTrajStartPos(const Vec2& pos)
{
	if (trajectories_.size())
	{
		auto& newestTraj = trajectories_.back();

		if (newestTraj)
		{
			newestTraj->SetTwoPoses(pos, newestTraj->GetTwoPoses().ePos);
		}
	}
}

#include "Trajectories.h"

void Trajectories::Init()
{
}


void Trajectories::Update()
{
	Update(0, nullptr);
}

void Trajectories::Update(float dirY, std::function<bool(float trajPos, float chargeGaugeRatio)> chargeGaugeFunc)
{
	//�ړ��ȂǍX�V����
	for (auto itr = trajectories_.begin(); itr != trajectories_.end(); itr++)
	{
		//�X�V
		itr->get()->SetScrollVec({ 0,(dirY) * 0.34f });
		itr->get()->Update(chargeGaugeFunc);

	}

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

void Trajectories::Draw()
{
	for (auto& trajs : trajectories_)
	{
		trajs->Draw();
	}
}

void Trajectories::SetNewestTrajSPos(const Vec2& pos)
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

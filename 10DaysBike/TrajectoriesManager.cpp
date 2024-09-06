#include "TrajectoriesManager.h"
#include "KeyboardInput.h"

const float TrajectoriesManager::TRAJ_SPEED = 16.0f;


void TrajectoriesManager::Init()
{
	Init({ 0,0 });
}

void TrajectoriesManager::Init(const Vec2& pos)
{
	pos_ = pos;
	oldPos_ = pos_;

	trajectories_.clear();
	color_ = COLOR_DEBUG;
}

void TrajectoriesManager::GenerateUpdate()
{
	GenerateTrajectory();
	oldPos_ = pos_;
}

void TrajectoriesManager::Update()
{
	Update(0);
}

void TrajectoriesManager::Update(float dirY)
{
	//1�t���[�����Ƃɐ������邽��
	GenerateUpdate();

	for (auto itr = trajectories_.begin(); itr != trajectories_.end(); itr++)
	{
		//��(�������V����)�̋O��
		auto nextTrajItr = itr;
		nextTrajItr++;

		if (nextTrajItr == trajectories_.end())
		{
			break;
		}

		if (nextTrajItr->get()->GetIsHead() == false
			&& itr != trajectories_.begin())
		{
			//���ɏo���O�Ղ̌��̓_���n�_�Ƃ���
			itr->get()->SetTwoPoses(
				nextTrajItr->get()->GetTwoPoses().ePos,
				itr->get()->GetTwoPoses().ePos);
		}

	}

	//�ړ��ȂǍX�V����
	for (auto itr = trajectories_.begin(); itr != trajectories_.end(); itr++)
	{
		//�X�V
		itr->get()->SetVec(Vec2(0, dirY).GetNormalize() * TRAJ_SPEED);
		itr->get()->Update();

	}

	for (auto itr = trajectories_.begin(); itr != trajectories_.end(); itr++)
	{
		//�����Ă�t���O�������ĂȂ��O�Ղ���������
		if (itr->get()->GetIsAlive() == false)
		{
			trajectories_.erase(itr);

			if (trajectories_.size() < 1)
			{
				break;
			}

			itr = trajectories_.begin();
		}
	}
}

void TrajectoriesManager::Draw()
{
	for (auto& traj : trajectories_)
	{
		traj->Draw();
	}


#ifdef _DEBUG
	DrawCircle(pos_.x, pos_.y, IObject2D::GetColorUsedForDrawing(), 10);
#endif // _DEBUG

}

void TrajectoriesManager::ProccesingTurning()
{
	isTurned = true;
}

//------------------------------------------------------------------------------------
void TrajectoriesManager::GenerateTrajectory()
{
	//�^�[�������玟�̋O�Ղ�擪�ɂ��邽��
	bool isHead = false;
	if (isTurned)
	{
		isHead = true;
		isTurned = false;
	}

	auto traj = std::make_unique<Trajectory>();

	//��U,���ňړ��ʂ����̂܂܃x�N�g���Ɏg��
	const Vec2 DIR_VEC = oldPos_ - pos_;

	//����y����������
	traj->Init({ pos_,oldPos_ }, Vec2{ 0,0 },
		isHead);


	trajectories_.push_back(std::move(traj));
}

#include "TrajectoriesManager.h"
#include "KeyboardInput.h"

const float TrajectoriesManager::TRAJ_SPEED = 10.0f;


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
	//1�t���[�����Ƃɐ������邽��
	GenerateUpdate();

	for (auto itr = --trajectories_.end(), end = trajectories_.begin(); itr != end; itr--)
	{
		//�X�V
		itr->get()->Update();

		//���̋O��
		auto nextItr = itr;
		nextItr++;

		if (itr->get()->GetIsHead() == false
			&& itr != --trajectories_.end())
		{
			//���ɏo���O�Ղ̌��̓_���n�_�Ƃ���
			itr->get()->SetTwoPoses(nextItr->get()->GetTwoPoses().ePos,
				itr->get()->GetTwoPoses().sPos);
		}
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
	auto traj = std::make_unique<Trajectory>();
	//��U,���ňړ��ʂ����̂܂܃x�N�g���Ɏg��
	const Vec2 DIR_VEC = oldPos_ - pos_;

	//�^�[�������玟�̋O�Ղ�擪�ɂ��邽��
	bool isHead = false;
	if (isTurned)
	{
		isHead = true;
		isTurned = false;
	}

	//����y����������
	traj->Init({ pos_,oldPos_ }, Vec2{ 0,DIR_VEC.GetNormalize().y } * TRAJ_SPEED,
		isHead);


	trajectories_.push_back(std::move(traj));
}

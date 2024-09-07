#include "Trajectories.h"

void Trajectories::Init()
{
}


void Trajectories::Update()
{
	Update(0);
}

void Trajectories::Update(float dirY)
{
	for (auto itr = trajectories_.begin(); itr != trajectories_.end(); itr++)
	{
		//次(自分より新しい)の軌跡
		auto nextTrajItr = itr;
		nextTrajItr++;

		if (nextTrajItr == trajectories_.end())
		{
			break;
		}

		if (itr != trajectories_.begin())
		{
			//一個後に出た軌跡の後ろの点を始点とする
			itr->get()->SetTwoPoses(
				nextTrajItr->get()->GetTwoPoses().ePos,
				itr->get()->GetTwoPoses().ePos);
		}

	}

	//移動など更新処理
	for (auto itr = trajectories_.begin(); itr != trajectories_.end(); itr++)
	{
		//更新
		itr->get()->SetScrollVec({ 0,-fabsf(dirY) * 0.34f });
		itr->get()->Update();

	}

	for (auto itr = trajectories_.begin(); itr != trajectories_.end(); itr++)
	{
		//生きてるフラグがたってない軌跡を消すため
		if (itr->get()->GetIsAlive() == false)
		{
			trajectories_.erase(itr);

			//要素が0になったら自分を配列から消してもらうため
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

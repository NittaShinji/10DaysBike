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
	//1フレームごとに生成するため
	GenerateUpdate();


	for (auto itr = --trajectories_.end(), end = trajectories_.begin(); itr != end; itr--)
	{
		//更新
		itr->get()->Update();

		//次の軌跡
		auto nextItr = itr;
		nextItr++;

		if (itr->get()->GetIsHead() == false
			&& itr != --trajectories_.end())
		{
			//一個後に出た軌跡の後ろの点を始点とする
			itr->get()->SetTwoPoses(nextItr->get()->GetTwoPoses().ePos,
				itr->get()->GetTwoPoses().sPos);
		}
	}

	for (auto itr = trajectories_.begin(); itr != trajectories_.end(); itr++)
	{
		//生きてるフラグがたってない軌跡を消すため
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
	//一旦,仮で移動量をそのままベクトルに使う
	const Vec2 DIR_VEC = oldPos_ - pos_;

	//ターンしたら次の軌跡を先頭にするため
	bool isHead = false;
	if (isTurned)
	{
		isHead = true;
		isTurned = false;
	}

	//仮でyだけ動かす
	traj->Init({ pos_,oldPos_ }, Vec2{ 0,DIR_VEC.GetNormalize().y } * TRAJ_SPEED,
		isHead);


	trajectories_.push_back(std::move(traj));
}

#include "TrajectoriesManager.h"
#include "KeyboardInput.h"

const float TrajectoriesManager::TRAJ_SPEED = 21.0f;


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

void TrajectoriesManager::GenerateUpdate(float dirY, std::function<bool(float)> shootGaugeFunc)
{
	GenerateTrajectory(dirY, shootGaugeFunc);
	oldPos_ = pos_;
}

void TrajectoriesManager::Update()
{
	Update(0, nullptr, nullptr);
}

void TrajectoriesManager::Update(float dirY, std::function<bool(float)> shootGaugeFunc,
	std::function<bool(float, float)> chargeGaugeFunc)
{
	const Vec2 TRAJ_VEC = Vec2(0, dirY).GetNormalize() * TRAJ_SPEED;

	//1フレームごとに生成するため
	GenerateUpdate(TRAJ_VEC.y, shootGaugeFunc);

	//移動など更新処理
	for (auto itr = trajectoriesArray_.begin(); itr != trajectoriesArray_.end(); itr++)
	{
		//更新
		itr->get()->Update(TRAJ_VEC.y, chargeGaugeFunc);

	}

	for (auto itr = trajectoriesArray_.begin(); itr != trajectoriesArray_.end(); itr++)
	{
		//生きてるフラグがたってない軌跡の配列を消すため
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

void TrajectoriesManager::ProccesingTurning()
{
	isTurned = true;
}

//------------------------------------------------------------------------------------
void TrajectoriesManager::GenerateTrajectory(float dirY, std::function<bool(float)> shootGaugeFunc)
{
	if (shootGaugeFunc(Trajectory::SHOOT_DECREMENT_GAUGE))
	{
		bool isHead = false;
		std::unique_ptr<Trajectories> trajectories = nullptr;
		//ターンしたら次の軌跡を先頭にするため新たな配列をつくる
		if (isTurned || trajectoriesArray_.size() == 0)
		{
			isHead = true;
			isTurned = false;

			trajectories = std::make_unique<Trajectories>();
		}
		//軌跡の配列がすでにあってターンしてないとき
		else
		{
			trajectories = std::move(trajectoriesArray_.back());
			trajectoriesArray_.pop_back();
		}

		//一旦,仮で移動量をそのままベクトルに使う
		const Vec2 DIR_VEC = oldPos_ - pos_;

		//仮でyだけ動かす軌跡を生成
		auto traj = std::make_unique<Trajectory>();
		traj->Init({ pos_,oldPos_ }, Vec2{ 0,dirY },
			isHead);

		//配列に追加
		trajectories->PushBackTraj(std::move(traj));

		//軌跡配列を配列に追加
		trajectoriesArray_.push_back(std::move(trajectories));
	}
}

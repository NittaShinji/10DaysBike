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

	//1フレームごとに生成するため
	GenerateUpdate(geneInfo, shootGaugeFunc);

	//移動など更新処理
	for (auto itr = trajectoriesArray_.begin(); itr != trajectoriesArray_.end(); itr++)
	{
		//更新
		itr->get()->Update(TRAJ_VEC.y, chargeGaugeFunc);

	}

	//一番新しい軌跡の位置を管理クラスと一緒にする
	SetNewestTrajPos();

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
		//ターンしたら次の軌跡を先頭にするため新たな配列をつくる
		if (isNewTrajs_ || trajectoriesArray_.size() == 0)
		{
			isHead = true;
			isNewTrajs_ = false;

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
		traj->Init({ pos_,oldPos_ }, Vec2{ 0,geneInfo.dirY },
			isHead);
		//太さや消費ゲージをセット
		traj->SetThickNessRate(geneInfo.trajThickRate);
		traj->SetChargeGaugeRate(geneInfo.trajCostRate);

		//配列に追加
		trajectories->PushBackTraj(std::move(traj));

		//軌跡配列を配列に追加
		trajectoriesArray_.push_back(std::move(trajectories));
	}
}

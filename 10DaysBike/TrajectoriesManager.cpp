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

	//1フレームごとに生成するため
	bool isDanger = GenerateUpdate(geneInfo, shootGaugeFunc);

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
	//1つの軌跡のげずるりょうとその削りをあと何回するかを送り、可能だったら撃つため
	if (shootGaugeFunc(Trajectory::SHOOT_DECREMENT_GAUGE * geneInfo.trajCostRate,
		geneInfo.continueNum))
	{
		bool isHead = false;
		std::unique_ptr<Trajectories> trajectories = nullptr;
		//ターンしたら次の軌跡を先頭にするため新たな配列をつくる
		if (isNewTrajs_ || trajectoriesArray_.size() == 0)
		{
			isHead = true;
			isNewTrajs_ = false;

			//下向いてるときはチャージ用の
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
		traj->SetName(geneInfo.name);

		//配列に追加
		trajectories->PushBackTraj(std::move(traj));

		//軌跡配列を配列に追加
		trajectoriesArray_.push_back(std::move(trajectories));

		return true;
	}

	return false;
}

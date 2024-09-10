#pragma once
#include"Trajectories.h"
#include<functional>

//線をまとめて軌跡に見せるためのクラス
class TrajectoriesManager : public IObject2D
{
public:
	//軌跡を生成するときに必要な情報
	struct TrajGenerateInform
	{
		float dirY = 0;
		float trajThickRate = 1.0f;
		float trajCostRate = 1.0f;
	};

public:
	static const float TRAJ_SPEED;
private:
	std::vector<std::unique_ptr<Trajectories>> trajectoriesArray_;
	Vec2 oldPos_ = { 0,0 };
	const ColorDxLib COLOR_DEBUG = { 255,255,0 };
	bool isNewTrajs_ = false;

public:
	~TrajectoriesManager() { trajectoriesArray_.clear(); }
private:
	void GenerateTrajectory(const TrajGenerateInform& geneInfo, std::function<bool(float decreGauge)> shootGaugeFunc);
	void GenerateUpdate(const TrajGenerateInform& geneInfo, std::function<bool(float decreGauge)> shootGaugeFunc);
private:
	void SetNewestTrajPos();
public:
	void Init()override;
	void Init(const Vec2& pos);
	void Update()override;
	void Update(const TrajGenerateInform& geneInfo, std::function<bool(float decreGauge)> shootGaugeFunc,
		std::function<bool(float trajPos, float chargeGaugeRatio)> chargeGaugeFunc);
	void Draw()override;
public:
	void ProccesingNewTrajs();
};


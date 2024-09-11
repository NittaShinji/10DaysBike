#pragma once
#include"Trajectory.h"
#include<vector>
#include<functional>

class Trajectories :public IObject2D
{
protected:
	std::vector<std::unique_ptr<Trajectory>> trajectories_;


protected:
	void UpdatePos(float dirY, std::function<bool(float trajPos, float chargeGaugeRatio)> chargeGaugeFunc);
	void StartPosProcess();
	void DeleteDeadTrajectories();
public:
	virtual void Init()override;
	virtual void Update()override;
	virtual void Update(float dirY, std::function<bool(float trajPos, float chargeGaugeRatio)> chargeGaugeFunc);
	virtual void Draw()override;
public:
	void PushBackTraj(std::unique_ptr<Trajectory> traj) { trajectories_.push_back(std::move(traj)); }
	void SetNewestTrajStartPos(const Vec2& pos);
};


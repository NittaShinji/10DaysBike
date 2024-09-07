#pragma once
#include"Trajectory.h"
#include<vector>

class Trajectories :public IObject2D
{
private:
	std::vector<std::unique_ptr<Trajectory>> trajectories_;


private:

public:
	void Init()override;
	void Update()override;
	void Update(float dirY);
	void Draw()override;
public:
	void PushBackTraj(std::unique_ptr<Trajectory> traj) { trajectories_.push_back(std::move(traj)); }
};


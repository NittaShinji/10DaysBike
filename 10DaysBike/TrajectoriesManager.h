#pragma once
#include"Trajectories.h"

//ü‚ğ‚Ü‚Æ‚ß‚Ä‹OÕ‚ÉŒ©‚¹‚é‚½‚ß‚ÌƒNƒ‰ƒX
class TrajectoriesManager : public IObject2D
{
public:
	static const float TRAJ_SPEED;
private:
	std::vector<std::unique_ptr<Trajectories>> trajectoriesArray_;
	Vec2 oldPos_ = { 0,0 };
	const ColorDxLib COLOR_DEBUG = { 255,255,0 };
	bool isTurned=false;

public:
	~TrajectoriesManager() { trajectoriesArray_.clear(); }
private:
	void GenerateTrajectory(float dirY);
	void GenerateUpdate(float dirY);
public:
	void Init()override;
	void Init(const Vec2& pos);
	void Update()override;
	void Update(float dirY);
	void Draw()override;
public:
	void ProccesingTurning();
};


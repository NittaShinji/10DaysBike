#pragma once
#include"Trajectories.h"
#include<functional>

//�����܂Ƃ߂ċO�ՂɌ����邽�߂̃N���X
class TrajectoriesManager : public IObject2D
{
public:
	static const float TRAJ_SPEED;
	static const float SHOOT_DECREMENT_GAUGE;
private:
	std::vector<std::unique_ptr<Trajectories>> trajectoriesArray_;
	Vec2 oldPos_ = { 0,0 };
	const ColorDxLib COLOR_DEBUG = { 255,255,0 };
	bool isTurned = false;

public:
	~TrajectoriesManager() { trajectoriesArray_.clear(); }
private:
	void GenerateTrajectory(float dirY, std::function<bool(float)> shootGaugeFunc);
	void GenerateUpdate(float dirY, std::function<bool(float)> shootGaugeFunc);
public:
	void Init()override;
	void Init(const Vec2& pos);
	void Update()override;
	void Update(float dirY, std::function<bool(float)> shootGaugeFunc);
	void Draw()override;
public:
	void ProccesingTurning();
};


#pragma once
#include"Trajectory.h"
#include<vector>

//�����܂Ƃ߂ċO�ՂɌ����邽�߂̃N���X
class TrajectoriesManager : public IObject2D
{
public:
	static const float TRAJ_SPEED;
private:
	std::vector<std::unique_ptr<Trajectory>> trajectories_;
	Vec2 oldPos_ = { 0,0 };
	const ColorDxLib COLOR_DEBUG = { 255,255,0 };
	bool isTurned=false;

public:
	~TrajectoriesManager() { trajectories_.clear(); }
private:
	void GenerateTrajectory();
	void GenerateUpdate();
public:
	void Init()override;
	void Init(const Vec2& pos);
	void Update()override;
	void Draw()override;
public:
	void ProccesingTurning();
};


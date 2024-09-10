#pragma once
#include "Enemy.h"
#include "TriangleEnemy.h"
#include "EnemyState.h"
#include "BulletManager.h"
#include<vector>

class EnemyManager
{
public:

	// ê}å`ÇÃå`
	enum EnmeyPopInfo {
		Up = 0,		// è„
		Right,	// âE
		Left,	// ç∂
	};

	const Vec2 kEnemyPopUP = Vec2(WINDOW_SIZE.x / 2, -100.0f);
	const Vec2 kEnemyPopLeft = Vec2(-300, 100.0f);
	const Vec2 kEnemyPopRight = Vec2(900, 100.0f);
	const int kMaxEnemyNum = 20;

private:
	std::vector<std::unique_ptr<IEnemy>> enemies_;
	std::unique_ptr<BulletManager> bulletManager_;
public:
	~EnemyManager() { enemies_.clear(); }
private:
	void GenerateBulletEnemy();
	void GenerateTriangleEnemy();

public:
	void Init();
	void Update();
	void Draw();

private:

	const float kWaitTime_ = 120.0f;
	float waitTimer_ = kWaitTime_;
};


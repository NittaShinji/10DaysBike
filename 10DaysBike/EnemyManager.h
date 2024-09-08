#pragma once
#include "Enemy.h"
#include "EnemyState.h"
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

private:
	std::vector<std::unique_ptr<Enemy>> enemies_;
public:
	//~EnemyManager() { enemies_.clear(); }
private:
	void GenerateEnemy();
public:
	void Init();
	void Update();
	void Draw();

private:

	const float kWaitTime_ = 120.0f;
	float waitTimer_ = kWaitTime_;
	int enemyDeadNum_ = 0;

public:

	int GetEnemyDeadNum() { return enemyDeadNum_; }
};


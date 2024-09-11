#pragma once
#include "BadEnemy.h"
#include "BulletFlyEnemy.h"
#include "WanderEnemy.h"
#include "BulletEnemyState.h"
#include "BulletManager.h"
#include <vector>
#include <sstream>

class EnemyManager
{
public:

	// 図形の形
	enum EnmeyPopInfo {
		Up = 0,		// 上
		Right,	// 右
		Left,	// 左
	};

	enum EnmeyNameNum {
		BAT = 5,
		BULLET_FLY,
		WANDER,
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

	//敵発生データの読み込み
	void LoadEnemyPopDate();
	//敵発生コマンドの更新
	void UpdateEnemyPopComands();
	//敵発生関数
	void GenerateBadEnemy();
	void GenerateBulletFlyEnemy();
	/*void GenerateBadEnemy(Vec2 pos);
	void GenerateBulletFlyEnemy(Vec2 pos);*/
	void GenerateWanderEnemy(Vec2* PlayerPos ,const Vec2& GeneratePos );


public:
	void Init();
	void Update();
	void Draw();

private:

	const float kWaitTime_ = 120.0f;
	float waitTimer_ = kWaitTime_;
	//敵発生コマンド
	std::stringstream enemyPopComands;

	//敵待機中フラグ
	bool isWaitEnemy_;

	//敵待機中タイマー
	int32_t enemyWaitTimer_;
};


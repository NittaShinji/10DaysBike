#pragma once
#include "BadEnemy.h"
#include "BulletFlyEnemy.h"
#include "WanderEnemy.h"
#include "BeamEnemy.h"
#include "BulletEnemyState.h"
#include "BulletManager.h"
#include <vector>
#include <sstream>

class EnemyManager
{
public:

	enum EnmeyNameNum {
		BAT = 0,
		BULLET_FLY = 1,
		WANDER = 2,
		BEAM = 3,
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
	void GenerateBadEnemy(const Vec2& GeneratePos);
	void GenerateBulletFlyEnemy(const Vec2& GeneratePos);
	void GenerateWanderEnemy(Vec2* PlayerPos ,const Vec2& GeneratePos );
	void GenerateBeamEnemy(Vec2* PlayerPos, const Vec2& GeneratePos);
	void GenerateBeamEnemy(Vec2* PlayerPos, const Vec2& GeneratePos, int32_t pattern);
	void GenerateBadEnemy(const Vec2& GeneratePos, const int32_t pattern);
	void GenerateBulletFlyEnemy(const Vec2& GeneratePos, const int32_t pattern);
	void GenerateWanderEnemy(Vec2* PlayerPos ,const Vec2& GeneratePos, const int32_t pattern);

public:
	void Init();
	void Update();
	void Draw();

	void SetPlayerPosPtr(Vec2* pPosPtr);

private:

	const float kWaitTime_ = 120.0f;
	float waitTimer_ = kWaitTime_;
	//敵発生コマンド
	std::stringstream enemyPopComands;

	//敵待機中フラグ
	bool isWaitEnemy_;

	//敵待機中タイマー
	int32_t enemyWaitTimer_;

	//プレイヤーの位置取得
	Vec2* playerPosPtr_ = nullptr;

	//敵の数
	int32_t enemyTotalNum = 0;
};


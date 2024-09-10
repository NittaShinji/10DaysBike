#pragma once
#include"IEnemy.h"
#include "CircleCollider.h"
#include"TrajectoriesManager.h"
#include "EnemyBullet.h"
#include <list>

//前方宣言
class IEnemyState;
class BulletManager;

//敵
class Enemy : public IEnemy
{
public:
	static const uint16_t PROT_ENEMY_DAMEGE_NUM = 1;
	static const uint16_t PROT_ENEMY_IMGAE_NUM = 4;

private:

	//軌跡の管理クラス
	//std::unique_ptr<TrajectoriesManager> trajManag_ = nullptr;
	//ステート
	std::unique_ptr<IEnemyState>state_ = nullptr;
	//敵の弾
	std::list<std::unique_ptr<EnemyBullet>> bullets_;

public:
	~Enemy();
	
private:
	void MoveUpdate();
public:
	void Init()override;
	void Init(const Vec2& pos);
	void Update()override;
	void Draw()override;
public:
	void ChangeState(std::unique_ptr<IEnemyState> state);
	void ProccesingNewTrajs();
	//衝突時に呼び出される関数
	void OnCollision(const CollisionInfo& info) override;
	
private:
	//int graphHandle_[PROT_ENEMY_IMGAE_NUM];
	int graphHandle_;

	BulletManager* bulletManager_ = nullptr;

public:

	std::list<std::unique_ptr<EnemyBullet>>& GetBullets() { return bullets_; };
	void SetBullletManger(BulletManager* bulletManager) { bulletManager_ = bulletManager; }
	BulletManager* GetBullletManager() { return bulletManager_; }
};


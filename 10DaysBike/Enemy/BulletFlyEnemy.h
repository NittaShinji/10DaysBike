#pragma once
#include"IBulletEnemy.h"
#include "CircleCollider.h"
#include"TrajectoriesManager.h"
#include "EnemyBullet.h"
#include <list>

//前方宣言
class IBulletEnemyState;
class BulletManager;

//飛行敵
class BulletFlyEnemy : public IBulletEnemy
{
public:
	static const uint16_t PROT_ENEMY_DAMEGE_NUM = 1;
	static const uint16_t PROT_ENEMY_IMGAE_NUM = 4;

private:

public:
	~BulletFlyEnemy();

public:

	void Init(const Vec2& pos,float bulletSpeed);
	void Update()override;
	void Draw()override;

	void SetPattern(int pattern) { pattern_ = pattern; };
public:

	//衝突時に呼び出される関数
	void OnCollision(const CollisionInfo& info) override;
	
private:

	static const uint16_t kBulletFlyEnemyImageNum_ = 4;
	static const double kBulletFlyEnemyImageScale_;
	int graphHandle_[kBulletFlyEnemyImageNum_];
	int imageNum_ = 0;

	int pattern_ = 0;
};


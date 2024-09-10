#pragma once
#include "IEnemy.h"
#include "CircleCollider.h"
#include"TrajectoriesManager.h"
#include "EnemyBullet.h"
#include <list>

//前方宣言
class BulletManager;

class TriangleEnemy : public IEnemy
{
public:
	static const uint16_t PROT_ENEMY_DAMEGE_NUM = 1;

private:

	//敵の弾
	std::list<std::unique_ptr<EnemyBullet>> bullets_;
	BulletManager* bulletManager_ = nullptr;
	//発射タイマー
	int32_t bulletCoolTimer_;
	//発射時間
	const float kBulletCoolTime_ = 60.0f;

public:
	~TriangleEnemy();

public:
	void Init()override;
	void Init(const Vec2& pos);
	void Update()override;
	void Draw()override;
public:

	//衝突時に呼び出される関数
	void OnCollision(const CollisionInfo& info) override;

public:

	//弾を発射
	void Fire();

public:

	std::list<std::unique_ptr<EnemyBullet>>& GetBullets() { return bullets_; };
	void SetBullletManger(BulletManager* bulletManager) { bulletManager_ = bulletManager; }
};


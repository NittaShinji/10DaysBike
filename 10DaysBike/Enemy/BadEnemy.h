#pragma once
#include "IEnemy.h"
#include "CircleCollider.h"
#include"TrajectoriesManager.h"
#include "EnemyBullet.h"
#include <list>

//前方宣言
class BulletManager;

class BadEnemy : public IEnemy
{
public:
	static const uint16_t PROT_ENEMY_DAMEGE_NUM = 1;
	static const uint16_t PROT_ENEMY_IMGAE_NUM = 4;
	static const double kBadEnemyImageScale_;

private:

	int graphHandle_;

	//目的地
	Vec2 targetPos_;     
	//移動速度
	const float moveSpeedY_ = 3.0f;  
	const float moveSpeedX_ = 3.5f;

	//動きパターンのローカル変数
	int32_t pattern_ = 0;

	//移動変数
	float moveAngle_ = 0;
	const float kAddmoveAngle_ = 0.05f;


public:
	~BadEnemy();

public:

	void Init(const Vec2& pos, const Vec2& targetPos);
	void Update()override;
	void Draw()override;
public:

	//衝突時に呼び出される関数
	void OnCollision(const CollisionInfo& info) override;
};


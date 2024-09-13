#pragma once
#include "IEnemy.h"
#include "CircleCollider.h"
#include"TrajectoriesManager.h"
#include "EnemyBullet.h"
#include <list>

//前方宣言
class BulletManager;

class WanderEnemy : public IEnemy
{
public:
	static const uint16_t PROT_ENEMY_DAMEGE_NUM = 1;
	static const uint16_t PROT_ENEMY_IMGAE_NUM = 4;

private:

	int graphHandle_[8];

	//目的地
	Vec2 targetPos_;
	Vec2* targetPosPtr_ = nullptr;
	//移動速度]
	int32_t homingFlameCount_;
	const int32_t excuteHomingFlameCount_ = 5;
	float moveSpeed_ = 3.0f;
	float moveVelocity_ = 0;
	const float kAddVelocity_ = 0.2f;
	Vec2 moveVec_ = {0,1};
	float homingAngle_ = 0.06f;
	const float kNearLen_ = 100.f;

	Vec2 oldMoveVec_ = {}; //移動ベクトル保存
	int32_t isHomingCount_ = 0;
	const int32_t kMaxHomingCount_ = 70;

	bool isHoming_ = true;


public:
	~WanderEnemy();

public:

	void Init(const Vec2& pos, Vec2* targetPos);
	void Update()override;
	void Draw()override;
public:

	//衝突時に呼び出される関数
	void OnCollision(const CollisionInfo& info) override;
};


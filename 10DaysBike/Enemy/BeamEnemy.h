#pragma once
#include"IBulletEnemy.h"
#include "CircleCollider.h"
#include"TrajectoriesManager.h"
#include "EnemyBullet.h"
#include <list>

//‘O•ûéŒ¾
class IBulletEnemyState;
class BulletManager;

//”òs“G
class BeamEnemy : public IBulletEnemy
{
public:
	static const uint16_t PROT_ENEMY_DAMEGE_NUM = 1;
	static const uint16_t PROT_ENEMY_IMGAE_NUM = 4;

private:

public:
	~BeamEnemy();

public:

	void Init(const Vec2& pos, float bulletSpeed);
	void Update()override;
	void Draw()override;

	void SetPattern(int32_t pattern) { pattern_ = pattern; };
public:

	//Õ“Ë‚ÉŒÄ‚Ño‚³‚ê‚éŠÖ”
	void OnCollision(const CollisionInfo& info) override;

private:

	static const uint16_t kBeamEnemyImageNum_ = 3;
	static const double kBeamEnemyImageScale_;
	int graphHandle_[kBeamEnemyImageNum_];
	int imageNum_ = 0;
	int32_t pattern_ = 0;
	bool isInvMove_ = false;

	Vec2 moveVec_;
	const Vec2 kMoveSpeed_ = { 3.f, 0.5f};



	enum ACTION_PHASE {
		Charge,
		Shot,
		Delay,
	};
	
	ACTION_PHASE actionPhase_ = Charge;

	int32_t chargeCount_ = 0;
	const int32_t kMaxChargeCount_ = 90;

	int32_t shotCount_ = 0;
	const int32_t kMaxShotCount_ = 100;

	int32_t bulletShotCount_ = 0;
	const int32_t kBulletShotCount_ = 2;

	int32_t delayCount_ = 0;
	const int32_t kMaxDelayCount_ = 60;

	bool isTopBullet_ = true;
};


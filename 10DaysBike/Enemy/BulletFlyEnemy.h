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
public:

	//Õ“Ë‚ÉŒÄ‚Ño‚³‚ê‚éŠÖ”
	void OnCollision(const CollisionInfo& info) override;
	
private:

	static const uint16_t kBulletFlyEnemyImageNum_ = 4;
	static const double kBulletFlyEnemyImageScale_;
	int graphHandle_[kBulletFlyEnemyImageNum_];
};


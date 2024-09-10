#pragma once
#include "IEnemy.h"
#include "CircleCollider.h"
#include"TrajectoriesManager.h"
#include "EnemyBullet.h"
#include <list>

//‘O•ûéŒ¾
class BulletManager;

class BadEnemy : public IEnemy
{
public:
	static const uint16_t PROT_ENEMY_DAMEGE_NUM = 1;
	static const uint16_t PROT_ENEMY_IMGAE_NUM = 4;

private:

	int graphHandle_;

public:
	~BadEnemy();

public:

	void Init(const Vec2& pos);
	void Update()override;
	void Draw()override;
public:

	//Õ“Ë‚ÉŒÄ‚Ño‚³‚ê‚éŠÖ”
	void OnCollision(const CollisionInfo& info) override;
};


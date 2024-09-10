#pragma once
#include "IEnemy.h"
#include "CircleCollider.h"
#include"TrajectoriesManager.h"
#include "EnemyBullet.h"
#include <list>

//�O���錾
class BulletManager;

class TriangleEnemy : public IEnemy
{
public:
	static const uint16_t PROT_ENEMY_DAMEGE_NUM = 1;

private:

	//�G�̒e
	std::list<std::unique_ptr<EnemyBullet>> bullets_;
	BulletManager* bulletManager_ = nullptr;
	//���˃^�C�}�[
	int32_t bulletCoolTimer_;
	//���ˎ���
	const float kBulletCoolTime_ = 60.0f;

public:
	~TriangleEnemy();

public:
	void Init()override;
	void Init(const Vec2& pos);
	void Update()override;
	void Draw()override;
public:

	//�Փˎ��ɌĂяo�����֐�
	void OnCollision(const CollisionInfo& info) override;

public:

	//�e�𔭎�
	void Fire();

public:

	std::list<std::unique_ptr<EnemyBullet>>& GetBullets() { return bullets_; };
	void SetBullletManger(BulletManager* bulletManager) { bulletManager_ = bulletManager; }
};


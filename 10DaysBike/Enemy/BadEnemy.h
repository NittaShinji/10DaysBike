#pragma once
#include "IEnemy.h"
#include "CircleCollider.h"
#include"TrajectoriesManager.h"
#include "EnemyBullet.h"
#include <list>

//�O���錾
class BulletManager;

class BadEnemy : public IEnemy
{
public:
	static const uint16_t PROT_ENEMY_DAMEGE_NUM = 1;
	static const uint16_t PROT_ENEMY_IMGAE_NUM = 4;
	static const double kBadEnemyImageScale_;

private:

	int graphHandle_;

	//�ړI�n
	Vec2 targetPos_;     
	//�ړ����x
	const float moveSpeedY_ = 3.0f;  
	const float moveSpeedX_ = 3.5f;

	//�����p�^�[���̃��[�J���ϐ�
	int32_t pattern_ = 0;

	//�ړ��ϐ�
	float moveAngle_ = 0;
	const float kAddmoveAngle_ = 0.05f;


public:
	~BadEnemy();

public:

	void Init(const Vec2& pos, const Vec2& targetPos);
	void Update()override;
	void Draw()override;
public:

	//�Փˎ��ɌĂяo�����֐�
	void OnCollision(const CollisionInfo& info) override;
};


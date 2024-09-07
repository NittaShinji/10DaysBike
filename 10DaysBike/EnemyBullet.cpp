#include "EnemyBullet.h"
#include <cassert>

EnemyBullet::EnemyBullet()
{
}

EnemyBullet::~EnemyBullet()
{
}

void EnemyBullet::Reset(Vec2 position)
{
	//��]�p
	radian_ = 0;
	//���s�ړ�
	//���@�̍��W���擾
	pos_ = position;
}

void EnemyBullet::Initialize(const Vec2& position, const Vec2& velocity)
{
	radius_ = kBulletRadius_;

	//�����Ŏ󂯎�������x�������o�ϐ��ɑ��
	velocity_ = velocity;

	//��]�p
	radian_ = 0;
	//���s�ړ�
	//���@�̍��W���擾
	pos_ = position;

	canMoved = true;
}

void EnemyBullet::Init()
{
}

void EnemyBullet::Update()
{
	if (canMoved == true)
	{
		//���W���ړ�������(1�t���[�����̈ړ��ʂ𑫂�����)
		pos_.y -= velocity_.y;
	}

	if (--deathTimer_ <= 0)
	{
		isDead_ = true;
	}
}

//�`��
void EnemyBullet::Draw()
{
	DrawCircle(pos_.x, pos_.y, radius_, GetColorUsedForDrawing(), true);
}
void EnemyBullet::Dead()
{
	isDead_ = true;
}

void EnemyBullet::OnCollision()
{
	//�f�X�t���O�𗧂Ă�
	isDead_ = true;
}

void EnemyBullet::OnCollisionStop()
{
	canMoved = false;
	deathTimer_ = 0;
}
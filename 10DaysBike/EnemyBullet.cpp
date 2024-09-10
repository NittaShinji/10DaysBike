#include "EnemyBullet.h"
#include "CollisionAttribute.h"
#include <cassert>

EnemyBullet::EnemyBullet()
{

}

EnemyBullet::~EnemyBullet()
{
	// �폜�t���O�������Ă���ꍇ�ɂ̂݃R���C�_�[���폜
	/*if (markedForDeletion_) {
		RemoveCollider();
	}*/
	RemoveCollider();
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

	//���O
	name_ = "enemyBullet";

	//��]�p
	radian_ = 0;
	//���s�ړ�
	//���@�̍��W���擾
	pos_ = position;

	//�R���C�_�[�̒ǉ�
	bulletCollider_ = std::make_unique<CircleCollider>(pos_, radius_);

	//�R���C�_�[�̓o�^
	SetCollider(bulletCollider_.get());

	//�������w��
	bulletCollider_->SetAttribute(COLLISION_ATTR_ENEMYS);

	coliderPos_ = pos_;

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

	coliderPos_ = pos_;
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
	isDeleteCollider_ = true;
	//RemoveCollider();
}

void EnemyBullet::OnCollisionStop()
{
	canMoved = false;
	deathTimer_ = 0;
}
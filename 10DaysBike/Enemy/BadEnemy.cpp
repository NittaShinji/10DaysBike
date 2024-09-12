#include "BadEnemy.h"
#include "BulletManager.h"
#include "CollisionAttribute.h"

BadEnemy::~BadEnemy()
{
	DeleteGraph(graphHandle_);
}

void BadEnemy::Init(const Vec2& pos, const Vec2& targetPos)
{
	//������
	IEnemy::Init(pos,"BadEnemy");
	
	//�摜�ǂݍ���
	graphHandle_ = LoadGraph((RESOUCE_PATH + "batEnemy.png").c_str());

	IEnemy::AddCollider();

	targetPos_ = targetPos;

	pattern_ = 1;
}

void BadEnemy::Update()
{
	if (pattern_ == 0) {
		float dx = targetPos_.x - pos_.x;
		float dy = targetPos_.y - pos_.y;
		float distance = sqrt(dx * dx + dy * dy);

		// �ړI�n�ɓ��B���������m�F
		if (distance > moveSpeedY_) {
			// �P�ʃx�N�g�����v�Z���Ĉړ�
			float ux = dx / distance;
			float uy = dy / distance;
			pos_.x += ux * moveSpeedY_;
			pos_.y += uy * moveSpeedY_;
		}
		else {
			// �ړI�n�ɓ��B������A�ʒu��ړI�n�ɌŒ�
			pos_.x = targetPos_.x;
			pos_.y = targetPos_.y;
		}
	}
	else if (pattern_ == 1) {
		moveAngle_ += kAddmoveAngle_;
		pos_.x += sinf(moveAngle_) * moveSpeedX_;
		pos_.y += moveSpeedY_;
	}
	else if (pattern_ == 2) {
		moveAngle_ += kAddmoveAngle_;
		pos_.x += sinf(moveAngle_) * -moveSpeedX_;
		pos_.y += moveSpeedY_;
	}

	

	IEnemy::Update();
}

void BadEnemy::Draw()
{
	IEnemy::Draw();
	const int* handles = nullptr;
	DrawGraph(pos_.x - radius_, pos_.y - radius_, graphHandle_, FALSE);
}

//----------------------------------------------------------------------

void BadEnemy::OnCollision(const CollisionInfo& info)
{
	IEnemy::OnCollision(info);
}

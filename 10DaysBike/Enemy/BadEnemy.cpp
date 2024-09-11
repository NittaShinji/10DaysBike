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
}

void BadEnemy::Update()
{
	float dx = targetPos_.x - pos_.x;
	float dy = targetPos_.y - pos_.y;
	float distance = sqrt(dx * dx + dy * dy);

	// �ړI�n�ɓ��B���������m�F
	if (distance > moveSpeed_) {
		// �P�ʃx�N�g�����v�Z���Ĉړ�
		float ux = dx / distance;
		float uy = dy / distance;
		pos_.x += ux * moveSpeed_;
		pos_.y += uy * moveSpeed_;
	}
	else {
		// �ړI�n�ɓ��B������A�ʒu��ړI�n�ɌŒ�
		pos_.x = targetPos_.x;
		pos_.y = targetPos_.y;
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

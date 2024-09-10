#include "BulletFlyEnemy.h"
#include "BulletEnemyState.h"
#include "BulletManager.h"
#include "CollisionAttribute.h"

const double BulletFlyEnemy::kBulletFlyEnemyImageScale_ = 1.0f;

BulletFlyEnemy::~BulletFlyEnemy()
{
	// �ǂݍ��񂾉摜�̃O���t�B�b�N�n���h�����폜
	for (int i = 0; i < kBulletFlyEnemyImageNum_; i++)
	{
		DeleteGraph(graphHandle_[i]);
	}
}

void BulletFlyEnemy::Init(const Vec2& pos,float bulletSpeed)
{
	//�摜�ǂݍ���
	LoadDivGraph((RESOUCE_PATH + "bulletFlyEnemy.png").c_str(), 4, 4, 1, 128, 128, graphHandle_);

	//������
	IBulletEnemy::Init(pos,bulletSpeed,"BulletFlyEnemy");

	hp_ = 1000;

	//�X�e�[�g
	ChangeState(std::make_unique<EnemyStateWait>());
}

void BulletFlyEnemy::Update()
{
	IBulletEnemy::Update();
}

void BulletFlyEnemy::Draw()
{
	IBulletEnemy::Draw();
	const int* handles = nullptr;
	DrawRotaGraph(pos_.x, pos_.y, kBulletFlyEnemyImageScale_, angle_, graphHandle_[0], TRUE, FALSE);
}

void BulletFlyEnemy::OnCollision(const CollisionInfo& info)
{
	IEnemy::OnCollision(info);
}

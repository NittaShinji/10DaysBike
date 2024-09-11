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
	imageNum_ = 0;
	hp_ = 1000;

	//�X�e�[�g
	ChangeState(std::make_unique<EnemyStateFireBullet>());
}

void BulletFlyEnemy::Update()
{
	IBulletEnemy::Update();

	// ���݂̃X�e�[�g�� EnemyStateFireBullet ���ǂ����`�F�b�N
	EnemyStateFireBullet* fireBulletState = dynamic_cast<EnemyStateFireBullet*>(state_.get());
	if (fireBulletState)
	{
		// bulletCoolTimer_ �̒l���擾
		int32_t bulletCoolTimer = fireBulletState->GetBulletCoolTimer();

		// bulletCoolTimer_ ���g���ĉ����������s��
		// ��: �^�C�}�[�����Z�b�g����邩�ǂ����m�F����
		int bulletGraphDivNum = EnemyStateFireBullet::kBulletCoolTime_ / PROT_ENEMY_IMGAE_NUM;

		if (bulletCoolTimer >= bulletGraphDivNum * 3 && bulletCoolTimer <= EnemyStateFireBullet::kBulletCoolTime_)
		{
			imageNum_ = 0;
		}
		else if (bulletCoolTimer >= bulletGraphDivNum * 2 && bulletCoolTimer <= bulletGraphDivNum * 3)
		{
			imageNum_ = 1;
		}
		else if (bulletCoolTimer >= bulletGraphDivNum && bulletCoolTimer <= bulletGraphDivNum * 2)
		{
			imageNum_ = 2;
		}
		else if (bulletCoolTimer >= 0 && bulletCoolTimer <= bulletGraphDivNum)
		{
			imageNum_ = 3;
		}
	}
}

void BulletFlyEnemy::Draw()
{
	IBulletEnemy::Draw();
	const int* handles = nullptr;
	DrawRotaGraph(pos_.x, pos_.y, kBulletFlyEnemyImageScale_, angle_, graphHandle_[imageNum_], TRUE, FALSE);
}

void BulletFlyEnemy::OnCollision(const CollisionInfo& info)
{
	IEnemy::OnCollision(info);
}

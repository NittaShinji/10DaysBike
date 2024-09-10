#include "BulletManager.h"

BulletManager::~BulletManager()
{
	bullets_.clear();
}

void BulletManager::Init()
{
	bullets_.clear();
}

void BulletManager::Update()
{
	//�f�X�t���O�̗������e���폜
	bullets_.remove_if([](std::unique_ptr<EnemyBullet>& bullet) {
		return bullet->IsDead();
	});

	//�e�X�V
	for (std::unique_ptr<EnemyBullet>& bullet : bullets_)
	{
		bullet->Update();
	}
}

void BulletManager::Draw()
{
	for (std::unique_ptr<EnemyBullet>& bullet : bullets_)
	{
		bullet->Draw();
	}
}

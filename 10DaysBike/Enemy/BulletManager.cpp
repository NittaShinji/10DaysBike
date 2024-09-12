#include "BulletManager.h"

BulletManager::BulletManager()
{

}

BulletManager::~BulletManager()
{
	bullets_.clear();
	
}

void BulletManager::Init()
{
	
	normalBulletGraph_ = LoadGraph((RESOUCE_PATH + "tama1.png").c_str());
	beamTopGraph_ = LoadGraph((RESOUCE_PATH + "beam1.png").c_str());
	beamLineGraph_ = LoadGraph((RESOUCE_PATH + "beam2.png").c_str());

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

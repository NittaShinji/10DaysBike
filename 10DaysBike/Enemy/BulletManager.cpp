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
	//デスフラグの立った弾を削除
	bullets_.remove_if([](std::unique_ptr<EnemyBullet>& bullet) {
		return bullet->IsDead();
	});

	//弾更新
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

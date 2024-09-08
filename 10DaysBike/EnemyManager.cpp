#include "EnemyManager.h"
#include <random>

void EnemyManager::Init()
{
	waitTimer_ = kWaitTime_;
	bulletManager_ = std::make_unique<BulletManager>();
}

void EnemyManager::Update()
{
	//デスフラグの立った敵を削除
	// 敵の削除（デスフラグの立ったものを削除）
	enemies_.erase(
		std::remove_if(enemies_.begin(), enemies_.end(),
		[](std::unique_ptr<Enemy>& enemy) {
		return enemy->IsDead();
	}),
	enemies_.end());

	if (waitTimer_ >= 0)
	{
		waitTimer_--;
		if (waitTimer_ < 0)
		{
			GenerateEnemy();
			waitTimer_ = kWaitTime_;
		}
	}

	for (std::unique_ptr<Enemy>& enemy : enemies_)
	{
		enemy->Update();
	}

	bulletManager_->Update();
}

void EnemyManager::Draw()
{
	for (std::unique_ptr<Enemy>& enemy : enemies_)
	{
		enemy->Draw();
	}

	bulletManager_->Draw();
}

void EnemyManager::GenerateEnemy()
{
	//乱数シード生成器
	std::random_device seed_gen;
	//メルセンヌツイスターの乱数エンジン
	std::mt19937_64 engine(seed_gen());
	//乱数範囲の指定
	std::uniform_int_distribution<int> dist(0, 2);

	// ランダムな値を取得
	int randomValue = dist(engine);

	// 敵の位置をランダムで生成
	Vec2 enemyPopPos;
	if (randomValue == Up)
	{
		enemyPopPos = kEnemyPopUP;
	}
	else if (randomValue == Up)
	{
		enemyPopPos = kEnemyPopLeft;
	}
	else
	{
		enemyPopPos = kEnemyPopRight;
	}

	//敵を生成し、初期化
	std::unique_ptr<Enemy> newEnemy = std::make_unique<Enemy>();
	newEnemy->Init(enemyPopPos);

	newEnemy->SetBullletManger(bulletManager_.get());

	//敵を登録する
	enemies_.push_back(std::move(newEnemy));
}

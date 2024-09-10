#include "BulletFlyEnemy.h"
#include "BulletEnemyState.h"
#include "BulletManager.h"
#include "CollisionAttribute.h"

const double BulletFlyEnemy::kBulletFlyEnemyImageScale_ = 1.0f;

BulletFlyEnemy::~BulletFlyEnemy()
{
	// 読み込んだ画像のグラフィックハンドルを削除
	for (int i = 0; i < kBulletFlyEnemyImageNum_; i++)
	{
		DeleteGraph(graphHandle_[i]);
	}
}

void BulletFlyEnemy::Init(const Vec2& pos,float bulletSpeed)
{
	//画像読み込み
	LoadDivGraph((RESOUCE_PATH + "bulletFlyEnemy.png").c_str(), 4, 4, 1, 128, 128, graphHandle_);

	//初期化
	IBulletEnemy::Init(pos,bulletSpeed,"BulletFlyEnemy");

	hp_ = 1000;

	//ステート
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

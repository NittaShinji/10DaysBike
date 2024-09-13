#include "BulletFlyEnemy.h"
#include "BulletEnemyState.h"
#include "BulletManager.h"
#include "CollisionAttribute.h"

const double BulletFlyEnemy::kBulletFlyEnemyImageScale_ = 0.3f;

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
	imageNum_ = 0;
	hp_ = 100;

	//ステート
	ChangeState(std::make_unique<EnemyStateFireBullet>());
}

void BulletFlyEnemy::Update()
{
	IBulletEnemy::Update();

	// 現在のステートが EnemyStateFireBullet かどうかチェック
	EnemyStateFireBullet* fireBulletState = dynamic_cast<EnemyStateFireBullet*>(state_.get());
	if (fireBulletState)
	{
		// bulletCoolTimer_ の値を取得
		int32_t bulletCoolTimer = fireBulletState->GetBulletCoolTimer();

		// 例: タイマーがリセットされるかどうか確認する
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

	if (pattern_ == 0) {
		pos_.x += 3.f;
		pos_.y += 4.f;
	}
	else if (pattern_ == 1) {
		pos_.x -= 3.f;
		pos_.y += 4.f;
	}
	else if (pattern_ == 2) {
		pos_.y += 4.f;
	}
}

void BulletFlyEnemy::Draw()
{
	IBulletEnemy::Draw();
	const int shakeRange = 2;
	if (isHit_ == true)
	{
		drawPos_.x += (rand() % (shakeRange * 2 + 1)) - shakeRange;  // ランダムに震える
		drawPos_.y += (rand() % (shakeRange * 2 + 1)) - shakeRange;  // ランダムに震える
		DrawRotaGraph(drawPos_.x, drawPos_.y, kBulletFlyEnemyImageScale_, angle_, graphHandle_[imageNum_], TRUE, FALSE);
	}
	else {
		DrawRotaGraph(pos_.x, pos_.y, kBulletFlyEnemyImageScale_, angle_, graphHandle_[imageNum_], TRUE, FALSE);
	}
}

void BulletFlyEnemy::OnCollision(const CollisionInfo& info)
{
	IEnemy::OnCollision(info);
}

#include "BadEnemy.h"
#include "BulletManager.h"
#include "CollisionAttribute.h"

const double BadEnemy::kBadEnemyImageScale_ = 1.0f;

BadEnemy::~BadEnemy()
{
	DeleteGraph(graphHandle_);
}

void BadEnemy::Init(const Vec2& pos, const Vec2& targetPos, const int pattern)
{
	//初期化
	IEnemy::Init(pos,"BadEnemy");
	
	//画像読み込み
	graphHandle_ = LoadGraph((RESOUCE_PATH + "batEnemy.png").c_str());

	IEnemy::AddCollider();

	targetPos_ = targetPos;

	pattern_ = pattern;
}

void BadEnemy::Update()
{
	if (pattern_ == 0) {
		float dx = targetPos_.x - pos_.x;
		float dy = targetPos_.y - pos_.y;
		float distance = sqrt(dx * dx + dy * dy);

		// 目的地に到達したかを確認
		if (distance > moveSpeedY_) {
			// 単位ベクトルを計算して移動
			float ux = dx / distance;
			float uy = dy / distance;
			pos_.x += ux * moveSpeedY_;
			pos_.y += uy * moveSpeedY_;
		}
		else {
			// 目的地に到達したら、位置を目的地に固定
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
	
	const int shakeRange = 2;
	if (isHit_ == true)
	{
		drawPos_.x += (rand() % (shakeRange * 2 + 1)) - shakeRange;  // ランダムに震える
		drawPos_.y += (rand() % (shakeRange * 2 + 1)) - shakeRange;  // ランダムに震える
		DrawRotaGraph(drawPos_.x, drawPos_.y, kBadEnemyImageScale_, angle_, graphHandle_, TRUE, FALSE);
	}
	else {
		DrawRotaGraph(pos_.x, pos_.y, kBadEnemyImageScale_, angle_, graphHandle_, TRUE, FALSE);
	}
	//DrawRotaGraph(pos_.x, pos_.y, kBadEnemyImageScale_, angle_, graphHandle_, TRUE, FALSE);
}

//----------------------------------------------------------------------

void BadEnemy::OnCollision(const CollisionInfo& info)
{
	IEnemy::OnCollision(info);
}

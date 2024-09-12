#include "BadEnemy.h"
#include "BulletManager.h"
#include "CollisionAttribute.h"

BadEnemy::~BadEnemy()
{
	DeleteGraph(graphHandle_);
}

void BadEnemy::Init(const Vec2& pos, const Vec2& targetPos)
{
	//初期化
	IEnemy::Init(pos,"BadEnemy");
	
	//画像読み込み
	graphHandle_ = LoadGraph((RESOUCE_PATH + "batEnemy.png").c_str());

	IEnemy::AddCollider();

	targetPos_ = targetPos;
}

void BadEnemy::Update()
{
	float dx = targetPos_.x - pos_.x;
	float dy = targetPos_.y - pos_.y;
	float distance = sqrt(dx * dx + dy * dy);

	// 目的地に到達したかを確認
	if (distance > moveSpeed_) {
		// 単位ベクトルを計算して移動
		float ux = dx / distance;
		float uy = dy / distance;
		pos_.x += ux * moveSpeed_;
		pos_.y += uy * moveSpeed_;
	}
	else {
		// 目的地に到達したら、位置を目的地に固定
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

#include "EnemyBullet.h"
#include <cassert>

EnemyBullet::EnemyBullet()
{
}

EnemyBullet::~EnemyBullet()
{
}

void EnemyBullet::Reset(Vec2 position)
{
	//回転角
	radian_ = 0;
	//平行移動
	//自機の座標を取得
	pos_ = position;
}

void EnemyBullet::Initialize(const Vec2& position, const Vec2& velocity)
{
	radius_ = kBulletRadius_;

	//引数で受け取った速度をメンバ変数に代入
	velocity_ = velocity;

	//回転角
	radian_ = 0;
	//平行移動
	//自機の座標を取得
	pos_ = position;

	canMoved = true;
}

void EnemyBullet::Init()
{
}

void EnemyBullet::Update()
{
	if (canMoved == true)
	{
		//座標を移動させる(1フレーム分の移動量を足しこむ)
		pos_.y -= velocity_.y;
	}

	if (--deathTimer_ <= 0)
	{
		isDead_ = true;
	}
}

//描画
void EnemyBullet::Draw()
{
	DrawCircle(pos_.x, pos_.y, radius_, GetColorUsedForDrawing(), true);
}
void EnemyBullet::Dead()
{
	isDead_ = true;
}

void EnemyBullet::OnCollision()
{
	//デスフラグを立てる
	isDead_ = true;
}

void EnemyBullet::OnCollisionStop()
{
	canMoved = false;
	deathTimer_ = 0;
}
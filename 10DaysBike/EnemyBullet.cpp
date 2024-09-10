#include "EnemyBullet.h"
#include "CollisionAttribute.h"
#include <cassert>

EnemyBullet::EnemyBullet()
{

}

EnemyBullet::~EnemyBullet()
{
	// 削除フラグが立っている場合にのみコライダーを削除
	/*if (markedForDeletion_) {
		RemoveCollider();
	}*/
	RemoveCollider();
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

	//名前
	name_ = "enemyBullet";

	//回転角
	radian_ = 0;
	//平行移動
	//自機の座標を取得
	pos_ = position;

	//コライダーの追加
	bulletCollider_ = std::make_unique<CircleCollider>(pos_, radius_);

	//コライダーの登録
	SetCollider(bulletCollider_.get());

	//属性を指定
	bulletCollider_->SetAttribute(COLLISION_ATTR_ENEMYS);

	coliderPos_ = pos_;

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

	coliderPos_ = pos_;
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
	isDeleteCollider_ = true;
	//RemoveCollider();
}

void EnemyBullet::OnCollisionStop()
{
	canMoved = false;
	deathTimer_ = 0;
}
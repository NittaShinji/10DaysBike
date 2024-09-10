#include "IEnemy.h"
#include "CollisionAttribute.h"

const float IEnemy::AUTO_MOVING_SPEED = 3.0f;
const float IEnemy::SIDE_MOVING_SPEED = 3.0f;
const ColorDxLib IEnemy::PROT_ENEMY_COLOR = { 255,128,128 };

IEnemy::~IEnemy()
{

}

void IEnemy::Init(){}

void IEnemy::Init(const Vec2& pos, std::string name)
{
	name_ = name;

	pos_ = pos;

	color_ = PROT_ENEMY_COLOR;

	radius_ = PROT_ENEMY_DRAWING_SIZE;
}

void IEnemy::Update()
{
	//攻撃を受けた判定をなくす(当たっていればOnCollision関数で再度trueになる)
	if (isHit_ == true)
	{
		isHit_ = false;
		color_ = { 255,128,128 };
	}

	//HPが0になったら死亡状態にし、コライダーを消すフラグをオンにする
	if (hp_ <= 0)
	{
		isDead_ = true;
		isDeleteCollider_ = true;
	}

	//現在位置をコライダー用の変数に渡す
	coliderPos_ = pos_;
}

void IEnemy::Draw()
{
	if (hp_ > 0)
	{
		unsigned int Cr;
		// 白の色コードを保存
		Cr = GetColor(255, 255, 255);
		DrawFormatString(100, 300, Cr, "敵HP : %d", hp_);
	}
}

void IEnemy::AddCollider()
{
	//コライダーの追加
	const float radius = static_cast<float>(PROT_ENEMY_DRAWING_SIZE);
	enemyCollider_ = std::make_unique<CircleCollider>(pos_, radius);

	//コライダーの登録
	SetCollider(enemyCollider_.get());

	//属性を指定
	enemyCollider_->SetAttribute(COLLISION_ATTR_ENEMYS);
}

void IEnemy::OnCollision(const CollisionInfo& info)
{
	if (isHit_ == false)
	{
		isHit_ = true;
		hp_ -= damageNum_;
		color_ = { 255,0,0 };
	}
}

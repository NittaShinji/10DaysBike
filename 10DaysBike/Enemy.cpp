#include "Enemy.h"
#include "EnemyState.h"
#include "CollisionAttribute.h"
const float Enemy::AUTO_MOVING_SPEED = 3.0f;
const float Enemy::SIDE_MOVING_SPEED = 3.0f;
const ColorDxLib Enemy::PROT_ENEMY_COLOR = { 255,128,128 };

void Enemy::MoveUpdate()
{

}

void Enemy::Init()
{
	Init({ 0,0 });
}

void Enemy::Init(const Vec2& pos)
{
	name_ = "enemy";

	pos_ = pos;

	color_ = PROT_ENEMY_COLOR;

	radius_ = PROT_ENEMY_DRAWING_SIZE;

	//trajManag_.reset();
	//trajManag_ = std::make_unique<TrajectoriesManager>();
	//trajManag_->Init(pos_);

	//コライダーの追加
	const float radius = static_cast<float>(PROT_ENEMY_DRAWING_SIZE);
	enemyCollider_ = std::make_unique<CircleCollider>(pos_, radius);

	//コライダーの登録
	SetCollider(enemyCollider_.get());

	//属性を指定
	enemyCollider_->SetAttribute(COLLISION_ATTR_ENEMYS);

	ProccesingTurning();

	//ステート
	ChangeState(std::make_unique<EnemyStateWait>());
}

void Enemy::Update()
{
	state_->Update();

	//trajManag_->SetPos(pos_);
	//trajManag_->Update();

	if (isHit_ == true)
	{
		isHit_ = false;
		color_ = { 255,128,128 };
	}
	coliderPos_ = pos_;
}

void Enemy::Draw()
{
	//trajManag_->Draw();
	state_->Draw();
}

//----------------------------------------------------------------------
void Enemy::ChangeState(std::unique_ptr<IEnemyState> state)
{
	state_.reset();
	state_ = std::move(state);
	state_->SetEnemyPtr(this);
	state_->Init();
}

void Enemy::OnCollision(const CollisionInfo& info)
{
 	if (isHit_ == false)
	{
		isHit_ = true;
		color_ = { 0,255,0 }; 
	}
}

void Enemy::ProccesingTurning()
{
	//trajManag_->ProccesingTurning();
}

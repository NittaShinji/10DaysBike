#include "Enemy.h"
#include "EnemyState.h"
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

	//ステート
	ChangeState(std::make_unique<EnemyStateWait>());
}

void Enemy::Update()
{
	state_->Update();
}

void Enemy::Draw()
{
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

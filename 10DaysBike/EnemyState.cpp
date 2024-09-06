#include "Enemy.h"
#include "EnemyState.h"

//----------------------------------------------------
//Šî’êƒNƒ‰ƒX
//void IEnemyState::SideMoveUpdate()
//{
//	const Vec2 SIDE_MOVE_VEC = {
//		KeyboardInput::GetInstance().GetSideVerticalKey().x,
//		0
//	};
//
//	enemy_->SetPos(enemy_->GetPos() + SIDE_MOVE_VEC * Enemy::SIDE_MOVING_SPEED);
//}

void IEnemyState::Update()
{
	/*SideMoveUpdate();

	if (KeyboardInput::GetInstance().GetTriggerKey(Enemy::TURN_KEY))
	{
		isWaitingTurn_ = true;
		enemy_->ProccesingTurning();
	}*/
}


//----------------------------------------------------
//“G‚Ì‘Ò‹@ó‘Ô
void EnemyStateWait::Init()
{
}

void EnemyStateWait::Update()
{
	enemy_->SetPos(enemy_->GetPos());

	IEnemyState::Update();


	/*if (isWaitingTurn_)
	{
		Enemy_->ChangeState(std::make_unique<EnemyStateDown>());
	}*/
}

void EnemyStateWait::Draw()
{
	const Vec2 pos = enemy_->GetPos();

	const Vec2 BOTTOM = pos - Vec2{ 0, -Enemy::PROT_ENEMY_DRAWING_SIZE };
	const Vec2 RIGHT_TOP = pos -
		Vec2{ Enemy::PROT_ENEMY_DRAWING_SIZE, Enemy::PROT_ENEMY_DRAWING_SIZE };
	const Vec2 LEFT_TOP = pos -
		Vec2{ -Enemy::PROT_ENEMY_DRAWING_SIZE, Enemy::PROT_ENEMY_DRAWING_SIZE };

	DrawTriangle(BOTTOM.x, BOTTOM.y, RIGHT_TOP.x, RIGHT_TOP.y, LEFT_TOP.x, LEFT_TOP.y,
		enemy_->GetColorUsedForDrawing(), true);
}


//----------------------------------------------------
//“G‚ÌUŒ‚ó‘Ô
void EnemyStateAttack::Init()
{
}

void EnemyStateAttack::Update()
{
	enemy_->SetPos(enemy_->GetPos() + Vec2{ 0, Enemy::AUTO_MOVING_SPEED });

	IEnemyState::Update();

	/*if (isWaitingTurn_)
	{
		Enemy_->ChangeState(std::make_unique<EnemyStateUp>());
	}*/
}

void EnemyStateAttack::Draw()
{
	const Vec2 pos = enemy_->GetPos();

	const Vec2 TOP = pos + Vec2{ 0, -Enemy::PROT_ENEMY_DRAWING_SIZE };
	const Vec2 RIGHT_BOTTOM = pos +
		Vec2{ Enemy::PROT_ENEMY_DRAWING_SIZE, Enemy::PROT_ENEMY_DRAWING_SIZE };
	const Vec2 LEFT_BOTTOM = pos +
		Vec2{ -Enemy::PROT_ENEMY_DRAWING_SIZE, Enemy::PROT_ENEMY_DRAWING_SIZE };

	DrawTriangle(TOP.x, TOP.y, RIGHT_BOTTOM.x, RIGHT_BOTTOM.y, LEFT_BOTTOM.x, LEFT_BOTTOM.y,
		enemy_->GetColorUsedForDrawing(), true);
}


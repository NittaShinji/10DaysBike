#include "PlayerState.h"
#include "Player.h"
#include "KeyboardInput.h"


//----------------------------------------------------
//基底クラス
void IPlayerState::SideMoveUpdate()
{
	const Vec2 SIDE_MOVE_VEC = {
		KeyboardInput::GetInstance().GetSideVerticalKey().x,
		0
	};

	player_->SetVec(SIDE_MOVE_VEC * Player::SIDE_MOVING_SPEED);
}

void IPlayerState::Update()
{
	SideMoveUpdate();

	//縦のベクトルセット
	const Vec2 VEC = player_->GetVec();
	player_->SetVec({ VEC.x,dirY_ });

	//移動
	player_->Move();

	if (KeyboardInput::GetInstance().GetTriggerKey(Player::TURN_KEY))
	{
		isWaitingTurn_ = true;
		player_->ProccesingTurning();
	}
}


//----------------------------------------------------
//プレイヤーが上向きの状態
void PlayerStateUp::Init()
{
	dirY_= -Player::AUTO_MOVING_SPEED;
}

void PlayerStateUp::Update()
{
	IPlayerState::Update();


	if (isWaitingTurn_)
	{
		player_->ChangeState(std::make_unique<PlayerStateDown>());
	}
}

void PlayerStateUp::Draw()
{
	const Vec2 pos = player_->GetPos();

	const Vec2 BOTTOM = pos - Vec2{ 0, -Player::PROT_PLAYER_DRAWING_SIZE };
	const Vec2 RIGHT_TOP = pos -
		Vec2{ Player::PROT_PLAYER_DRAWING_SIZE, Player::PROT_PLAYER_DRAWING_SIZE };
	const Vec2 LEFT_TOP = pos -
		Vec2{ -Player::PROT_PLAYER_DRAWING_SIZE, Player::PROT_PLAYER_DRAWING_SIZE };

	DrawTriangle(BOTTOM.x, BOTTOM.y, RIGHT_TOP.x, RIGHT_TOP.y, LEFT_TOP.x, LEFT_TOP.y,
		player_->GetColorUsedForDrawing(), true);
}


//----------------------------------------------------
//した向きの状態
void PlayerStateDown::Init()
{
	dirY_ = Player::AUTO_MOVING_SPEED;
}

void PlayerStateDown::Update()
{
	IPlayerState::Update();

	if (isWaitingTurn_)
	{
		player_->ChangeState(std::make_unique<PlayerStateUp>());
	}
}

void PlayerStateDown::Draw()
{
	const Vec2 pos = player_->GetPos();

	const Vec2 TOP = pos + Vec2{ 0, -Player::PROT_PLAYER_DRAWING_SIZE };
	const Vec2 RIGHT_BOTTOM = pos +
		Vec2{ Player::PROT_PLAYER_DRAWING_SIZE, Player::PROT_PLAYER_DRAWING_SIZE };
	const Vec2 LEFT_BOTTOM = pos +
		Vec2{ -Player::PROT_PLAYER_DRAWING_SIZE, Player::PROT_PLAYER_DRAWING_SIZE };

	DrawTriangle(TOP.x, TOP.y, RIGHT_BOTTOM.x, RIGHT_BOTTOM.y, LEFT_BOTTOM.x, LEFT_BOTTOM.y,
		player_->GetColorUsedForDrawing(), true);
}


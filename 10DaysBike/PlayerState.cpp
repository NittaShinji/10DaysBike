#include "PlayerState.h"
#include "Player.h"
#include "KeyboardInput.h"
#include "Easing.h"


const float IBurstState::BURST_THICK_RATE = 3.0f;
const float IBurstState::BURST_COST_RATE = 8.0f;
const float IBurstState::BURST_SPEED_RATE = 11.5f;


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

void IPlayerState::TurnPlayerUpdate()
{
	if (KeyboardInput::GetInstance().GetTriggerKey(Player::TURN_KEY))
	{
		isWaitingTurn_ = true;
		player_->ProccesingNewTrajs();
	}
	//バースト
	if (KeyboardInput::GetInstance().GetTriggerKey(Player::BURST_KEY))
	{
		isWaitingBurst_ = true;
		player_->ProccesingNewTrajs();
	}
}

void IPlayerState::UpDraw()
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

void IPlayerState::DownDraw()
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

void IPlayerState::Update(std::function<void(float thickRate, float costRate)> shootFunc)
{
	SideMoveUpdate();

	//縦のベクトルセット
	const Vec2 VEC = player_->GetVec();
	player_->SetVec({ VEC.x / player_->GetMoveSpeedRate(), dirY_ * player_->GetMoveSpeedRate() });

	//移動
	player_->Move();

	//軌跡管理クラスの位置も更新
	player_->TrajManagerPosUpdate();

	//エラー回避
	shootFunc;
}


//----------------------------------------------------
//プレイヤーが上向きの状態
void PlayerStateUp::Init()
{
	dirY_ = -Player::AUTO_MOVING_SPEED;
	//新しい奇跡の配列
	player_->ProccesingNewTrajs();
}

void PlayerStateUp::Update(std::function<void(float thickRate, float costRate)> shootFunc)
{
	IPlayerState::Update(nullptr);

	//軌跡の太さとかコストをセットして生成
	shootFunc(1.0f, 1.0f);

	TurnPlayerUpdate();

	if (isWaitingTurn_)
	{
		player_->ChangeState(std::make_unique<PlayerStateDown>());
	}
	else if (isWaitingBurst_)
	{
		player_->ChangeState(std::make_unique<PlayerStateBurstUp>());
	}
}

void PlayerStateUp::Draw()
{
	UpDraw();
}


//----------------------------------------------------
//した向きの状態
void PlayerStateDown::Init()
{
	dirY_ = Player::AUTO_MOVING_SPEED;
	//新しい奇跡の配列
	player_->ProccesingNewTrajs();
}

void PlayerStateDown::Update(std::function<void(float thickRate, float costRate)> shootFunc)
{
	IPlayerState::Update(nullptr);

	//軌跡の太さとかコストをセットして生成
	shootFunc(1.0f, 1.0f);

	TurnPlayerUpdate();

	if (isWaitingTurn_)
	{
		player_->ChangeState(std::make_unique<PlayerStateUp>());
	}
	else if (isWaitingBurst_)
	{
		player_->ChangeState(std::make_unique<PlayerStateBurstDown>());
	}
}

void PlayerStateDown::Draw()
{
	DownDraw();
}


//-------------------------------------------------------------------------------------------------
//バースト状態の親ステート
void IBurstState::Update(std::function<void(float thickRate, float costRate)> shootFunc)
{
	timer_--;

	float t = timer_ / (float)timerMax_;

	//移動スピード変更
	player_->SetMoveSpeedRate(
		Lerp(1.0f, BURST_SPEED_RATE, EaseOut(t))
	);

	IPlayerState::Update(nullptr);

	//軌跡の太さとかコストをセットして生成
	shootFunc(Lerp(1.0f, BURST_THICK_RATE, EaseOut(t))
		, Lerp(1.0f, BURST_COST_RATE, EaseOut(t))
	);
}


//--------------------------------------------------
//上向きのバースト状態
void PlayerStateBurstUp::Init()
{
	dirY_ = -Player::AUTO_MOVING_SPEED;
	timerMax_ = STATE_TIME;
	timer_ = STATE_TIME;
}

void PlayerStateBurstUp::Update(std::function<void(float thickRate, float costRate)> shootFunc)
{
	IBurstState::Update(shootFunc);

	if (timer_ < 1)
	{
		player_->ChangeState(std::make_unique<PlayerStateUp>());
	}
}

void PlayerStateBurstUp::Draw()
{
	UpDraw();
}


//--------------------------------------------------
//下向きのバースト
void PlayerStateBurstDown::Init()
{
	dirY_ = Player::AUTO_MOVING_SPEED;
	timerMax_ = STATE_TIME;
	timer_ = STATE_TIME;
}

void PlayerStateBurstDown::Update(std::function<void(float thickRate, float costRate)> shootFunc)
{
	IBurstState::Update(shootFunc);

	if (timer_ < 1)
	{
		player_->ChangeState(std::make_unique<PlayerStateDown>());
	}
}

void PlayerStateBurstDown::Draw()
{
	DownDraw();
}

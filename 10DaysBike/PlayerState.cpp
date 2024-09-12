#include "PlayerState.h"
#include "Player.h"
#include "KeyboardInput.h"
#include "Easing.h"
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

void IPlayerState::TurnPlayerUpdate(bool isTurn, bool isBurst)
{
	if (KeyboardInput::GetInstance().GetTriggerKey(Player::TURN_KEY) || isTurn)
	{
		TurnProcces();
	}
	//バースト
	if (KeyboardInput::GetInstance().GetTriggerKey(Player::BURST_KEY) || isBurst)
	{
		isWaitingBurst_ = true;
		player_->ProccesingNewTrajs();
	}
}

void IPlayerState::UpDraw()
{
	player_->DrawImage(useImageName_, 0, isSideTurnImage_);
}

void IPlayerState::DownDraw()
{
	player_->DrawImage(useImageName_, Player::DOWN_IMAGE_ANGLE, isSideTurnImage_);
}

void IPlayerState::Update(std::function<bool(float thickRate, float costRate)> shootFunc)
{

}

void IPlayerState::Update(std::function<bool(float thickRate, float costRate)> shootFunc, bool isUp)
{
	SideMoveUpdate();

	//縦のベクトルセット
	const Vec2 VEC = player_->GetVec();
	player_->SetVec({ VEC.x / player_->GetMoveSpeedRate(), dirY_ * player_->GetMoveSpeedRate() });

	//移動
	player_->Move();

	//軌跡管理クラスの位置も更新
	player_->TrajManagerPosUpdate();

	//アニメーション更新
	AnimationUpdate(isUp);

	//エラー回避
	shootFunc;
}

void IPlayerState::AnimationUpdate(bool isUp)
{
	//アニメーション用
	animeTimer_++;

	//横に傾く
	if (KeyboardInput::GetInstance().GetHitSideKey())
	{
		useImageName_ = Player::CURVE_IMAGE_NAME;

		bool isTurnKey = false;

		if (isUp)
		{
			isTurnKey = KeyboardInput::GetInstance().GetHitLeftKey();
		}
		else
		{
			isTurnKey = KeyboardInput::GetInstance().GetHitRightKey();
		}

		//画像反転するため
		if (isTurnKey)
		{
			isSideTurnImage_ = true;
		}
		else
		{
			isSideTurnImage_ = false;
		}

		//移動キーを押した瞬間アニメーションを最初からにするため
		if (KeyboardInput::GetInstance().GetTriggerSideKey())
		{
			player_->ImageIndexReset();
		}

		if (animeTimer_ % Player::CURVE_ANIME_INTERVAL == 0)
		{
			player_->IncrementImageIndex(Player::CURVE_IMAGE_NAME);
		}
	}
	//走ってるとき
	else
	{
		useImageName_ = Player::NORMAL_IMAGE_NAME;

		if (animeTimer_ % Player::NORMAL_ANIME_INTERVAL == 0)
		{
			player_->IncrementImageIndex(Player::NORMAL_IMAGE_NAME);
		}
	}
}

void IPlayerState::TurnProcces()
{
	isWaitingTurn_ = true;
	player_->ProccesingNewTrajs();
}

//----------------------------------------------------
//プレイヤーが上向きの状態
void PlayerStateUp::Init()
{
	dirY_ = -Player::AUTO_MOVING_SPEED;
	//新しい奇跡の配列
	player_->ProccesingNewTrajs();
}

void PlayerStateUp::Update(std::function<bool(float thickRate, float costRate)> shootFunc)
{
	IPlayerState::Update(nullptr, true);

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

void PlayerStateDown::Update(std::function<bool(float thickRate, float costRate)> shootFunc)
{
	IPlayerState::Update(nullptr, false);

	//軌跡の太さとかコストをセットして生成
	bool isDanger = !shootFunc(1.0f, 1.0f);
	//ゲージ切れそうならターンするため
	TurnPlayerUpdate(isDanger);

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
void IBurstState::Update(std::function<bool(float thickRate, float costRate)> shootFunc)
{
	timer_--;

	float t = timer_ / (float)timerMax_;

	//移動スピード変更
	player_->SetMoveSpeedRate(
		Lerp(1.0f, BURST_SPEED_RATE, EaseOut(t))
	);

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

void PlayerStateBurstUp::Update(std::function<bool(float thickRate, float costRate)> shootFunc)
{
	IBurstState::Update(shootFunc);
	IPlayerState::Update(nullptr, true);

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

void PlayerStateBurstDown::Update(std::function<bool(float thickRate, float costRate)> shootFunc)
{
	IBurstState::Update(shootFunc);
	IPlayerState::Update(nullptr, false);

	if (timer_ < 1)
	{
		player_->ChangeState(std::make_unique<PlayerStateDown>());
	}
}

void PlayerStateBurstDown::Draw()
{
	DownDraw();
}

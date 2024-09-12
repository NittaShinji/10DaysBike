#include "PlayerState.h"
#include "Player.h"
#include "KeyboardInput.h"
#include "Easing.h"
#include "Easing.h"


const float IBurstState::BURST_THICK_RATE = 3.0f;
const float IBurstState::BURST_COST_RATE = 8.0f;
const float IBurstState::BURST_SPEED_RATE = 11.5f;



//----------------------------------------------------
//���N���X
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
	//�o�[�X�g
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

	//�c�̃x�N�g���Z�b�g
	const Vec2 VEC = player_->GetVec();
	player_->SetVec({ VEC.x / player_->GetMoveSpeedRate(), dirY_ * player_->GetMoveSpeedRate() });

	//�ړ�
	player_->Move();

	//�O�ՊǗ��N���X�̈ʒu���X�V
	player_->TrajManagerPosUpdate();

	//�A�j���[�V�����X�V
	AnimationUpdate(isUp);

	//�G���[���
	shootFunc;
}

void IPlayerState::AnimationUpdate(bool isUp)
{
	//�A�j���[�V�����p
	animeTimer_++;

	//���ɌX��
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

		//�摜���]���邽��
		if (isTurnKey)
		{
			isSideTurnImage_ = true;
		}
		else
		{
			isSideTurnImage_ = false;
		}

		//�ړ��L�[���������u�ԃA�j���[�V�������ŏ�����ɂ��邽��
		if (KeyboardInput::GetInstance().GetTriggerSideKey())
		{
			player_->ImageIndexReset();
		}

		if (animeTimer_ % Player::CURVE_ANIME_INTERVAL == 0)
		{
			player_->IncrementImageIndex(Player::CURVE_IMAGE_NAME);
		}
	}
	//�����Ă�Ƃ�
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
//�v���C���[��������̏��
void PlayerStateUp::Init()
{
	dirY_ = -Player::AUTO_MOVING_SPEED;
	//�V������Ղ̔z��
	player_->ProccesingNewTrajs();
}

void PlayerStateUp::Update(std::function<bool(float thickRate, float costRate)> shootFunc)
{
	IPlayerState::Update(nullptr, true);

	//�O�Ղ̑����Ƃ��R�X�g���Z�b�g���Đ���
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
//���������̏��
void PlayerStateDown::Init()
{
	dirY_ = Player::AUTO_MOVING_SPEED;
	//�V������Ղ̔z��
	player_->ProccesingNewTrajs();
}

void PlayerStateDown::Update(std::function<bool(float thickRate, float costRate)> shootFunc)
{
	IPlayerState::Update(nullptr, false);

	//�O�Ղ̑����Ƃ��R�X�g���Z�b�g���Đ���
	bool isDanger = !shootFunc(1.0f, 1.0f);
	//�Q�[�W�؂ꂻ���Ȃ�^�[�����邽��
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
//�o�[�X�g��Ԃ̐e�X�e�[�g
void IBurstState::Update(std::function<bool(float thickRate, float costRate)> shootFunc)
{
	timer_--;

	float t = timer_ / (float)timerMax_;

	//�ړ��X�s�[�h�ύX
	player_->SetMoveSpeedRate(
		Lerp(1.0f, BURST_SPEED_RATE, EaseOut(t))
	);

	//�O�Ղ̑����Ƃ��R�X�g���Z�b�g���Đ���
	shootFunc(Lerp(1.0f, BURST_THICK_RATE, EaseOut(t))
		, Lerp(1.0f, BURST_COST_RATE, EaseOut(t))
	);
}


//--------------------------------------------------
//������̃o�[�X�g���
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
//�������̃o�[�X�g
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

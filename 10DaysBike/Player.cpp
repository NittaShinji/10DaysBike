#include "Player.h"
#include "PlayerState.h"
const float Player::AUTO_MOVING_SPEED = 3.0f;
const float Player::SIDE_MOVING_SPEED = 3.0f;
const ColorDxLib Player::PROT_PLAYER_COLOR = { 255,255,255 };


void Player::MoveUpdate()
{

}

void Player::Init()
{
	Init({ 0,0 });
}

void Player::Init(const Vec2& pos)
{
	name_ = "player";

	pos_ = pos;

	color_ = PROT_PLAYER_COLOR;

	//軌跡管理クラス
	trajManag_.reset();
	trajManag_ = std::make_unique<TrajectoriesManager>();
	trajManag_->Init(pos_);

	//ステート
	ChangeState(std::make_unique<PlayerStateDown>());
}

void Player::Update()
{
	state_->Update();

	trajManag_->SetPos(pos_);
	trajManag_->Update();
}

void Player::Draw()
{
	trajManag_->Draw();

	state_->Draw();
}


//----------------------------------------------------------------------
void Player::ChangeState(std::unique_ptr<IPlayerState> state)
{
	state_.reset();
	state_ = std::move(state);
	state_->SetPlayerPtr(this);
	state_->Init();
}

void Player::ProccesingTurning()
{
	trajManag_->ProccesingTurning();
}
